#include "../headers/Character.hpp"
#include <limits>
#include <stdexcept>
#include "../headers/Constants.hpp"

Character::Character(std::filesystem::path path1, float speed, float x, float y, int currentFrame, int framesCounter,
                     int framesSpeed, int currentLine, bool is_jumping) :
    m_path_character(std::move(path1)), m_position{x, y}, m_currentFrame(currentFrame), m_framesCounter(framesCounter),
    m_framesSpeed(framesSpeed), m_currentLine(currentLine), m_is_jumping(is_jumping), m_speed(speed) {
    m_character = LoadTexture(m_path_character.string().c_str());
    m_frame_rec = {0.0f, 0.0f, static_cast<float>(m_character.width) / constants::CHARACTER_FRAME_DIVISOR,
                   static_cast<float>(m_character.height)};
}

Character::~Character() { UnloadTexture(m_character); }

auto Character::update(bool input_jump, bool input_dash, const std::vector<std::unique_ptr<Platform>> &bottomPlatforms,
                       const std::vector<std::unique_ptr<Platform>> &topPlatforms) -> bool {
    bool was_grounded = m_is_grounded;
    if (!m_is_jumping) {
        bool groundedBottom = checkGrounded(bottomPlatforms);
        bool groundedTop = checkGrounded(topPlatforms);
        m_is_grounded = groundedBottom || groundedTop;
    }
    if (!was_grounded && m_is_grounded)
        m_jumps_left = config::JUMPS_NUMBER;
    handleJump(input_jump);
    float dt = GetFrameTime();
    if (m_dash_cooldown_timer > 0)
        m_dash_cooldown_timer -= dt;
    handleDash(input_dash);
    if (!m_is_grounded)
        applyGravity();
    if (checkRightCollision(bottomPlatforms) || checkRightCollision(topPlatforms) ||
        checkTopCollision(bottomPlatforms) || checkTopCollision(topPlatforms)) {
        m_is_alive = false;
        return false;
    }
    m_position.y += m_vertical_velocity;
    m_is_grounded ? run() : roll();
    if (m_position.y > config::SCREEN_HEIGHT) {
        m_is_alive = false;
        return false;
    }
    return true;
}

auto Character::draw() -> void {
    Vector2 origin = {m_frame_rec.width / 2.0f, m_frame_rec.height / 2.0f};
    Rectangle dest = {m_position.x + origin.x, m_position.y + origin.y, m_frame_rec.width, m_frame_rec.height};
    DrawTexturePro(m_character, m_frame_rec, dest, origin, m_rotation, WHITE);
}

auto Character::changeSpeed(int speed) -> void {
    if (speed > character_const::MAX_SPEED) {
        m_framesSpeed = 1;
    }
    else {
        m_framesSpeed = (character_const::MAX_SPEED - speed) - speed;
    }
}

auto Character::getDashBoost(float dt) const -> float { return m_is_dashing ? 1000.0f * dt : 0.0f; }

auto Character::getCollisionRect() const -> Rectangle {
    return {m_position.x, m_position.y, m_frame_rec.width, m_frame_rec.height};
}

auto Character::applyGravity() -> void {
    m_vertical_velocity += m_gravity;
    if (m_vertical_velocity > constants::MAX_VERTICAL_VELOCITY) {
        m_vertical_velocity = constants::MAX_VERTICAL_VELOCITY;
    }
}

auto Character::updateDeadAnimation() -> void {
    m_explosionFramesCounter++;
    if (m_explosionFramesCounter > constants::EXPLOSION_FPS) {
        m_explosionFramesCounter = 0;
        m_explosionCurrentFrame++;
        if (m_explosionCurrentFrame >= constants::EXPLOSION_MAX_FRAME) {
            m_explosionCurrentFrame = 0;
            m_explosionCurrentLine++;
            if (m_explosionCurrentLine >= constants::EXPLOSION_MAX_LINE) {
                m_explosionCurrentLine = constants::EXPLOSION_MAX_LINE - 1;
                m_deadAnimationFinished = true;
            }
        }
    }
}

auto Character::handleJump(bool input_jump) -> void {
    if (input_jump) {
        if ((m_is_grounded || m_jumps_left > 0) && !m_is_jumping) {
            if (!m_is_grounded)
                m_jumps_left--;
            m_is_jumping = true;
            m_jump_timer = 0.0f;
            m_vertical_velocity = m_jump_force;
        }
        else if (m_is_jumping && m_jump_timer < m_max_jump_time) {
            m_jump_timer += GetFrameTime();
            float jumpFactor = 1.0f - (m_jump_timer / m_max_jump_time);
            m_vertical_velocity = m_jump_force * jumpFactor;
        }
    }
    else {
        m_is_jumping = false;
    }
}

auto Character::handleDash(bool input_dash) -> void {
    float dt = GetFrameTime();
    if (input_dash && !m_is_dashing && m_dash_cooldown_timer <= 0.0f) {
        m_is_dashing = true;
        m_dash_timer = 0.0f;
        m_dash_cooldown_timer = m_max_dash_cooldown;
    }
    if (m_is_dashing) {
        m_dash_timer += dt;
        if (m_dash_timer >= m_max_dash_time) {
            m_is_dashing = false;
        }
    }
}

auto Character::run() -> void {
    m_rotation = 0.0f;
    m_framesCounter++;
    if (m_framesCounter > m_framesSpeed) {
        m_framesCounter = 0;
        m_currentFrame++;
        if (m_currentFrame > constants::MAX_CHARACTER_FRAME) {
            m_currentFrame = 0;
        }
        m_frame_rec.x = static_cast<float>(m_currentFrame) *
                        (static_cast<float>(m_character.width) / constants::CHARACTER_FRAME_DIVISOR);
    }
}

auto Character::roll() -> void { m_rotation += 10.0f; }

auto Character::checkGrounded(const std::vector<std::unique_ptr<Platform>> &platforms) -> bool {
    float bottom = m_position.y + m_frame_rec.height;
    float left = m_position.x;
    float right = m_position.x + m_frame_rec.width;
    float bestY = std::numeric_limits<float>::max();
    bool collisionFound = false;

    for (auto const &p: platforms) {
        if (right <= p->getX() || left >= p->getX() + p->getTexture().width * p->getScale()) {
            continue;
        }
        for (int i = 0; i < constants::NUM_SAMPLES; ++i) {
            float sampleX = left + i * (m_frame_rec.width / (constants::NUM_SAMPLES - 1));
            for (float offset = 0.0f; offset <= constants::GROUND_SCAN_RANGE; offset += constants::GROUND_STEP) {
                auto [sx, sy] = std::pair{sampleX, bottom + offset};
                if (p->checkCollision({sx, sy})) {
                    float candidateY = sy;
                    while (candidateY - constants::GROUND_STEP > bottom) {
                        auto [ux, uy] = std::pair{sx, candidateY - constants::GROUND_STEP};
                        if (!p->checkCollision({ux, uy}))
                            break;
                        candidateY -= constants::GROUND_STEP;
                    }
                    if (candidateY < bestY)
                        bestY = candidateY;
                    collisionFound = true;
                    break;
                }
            }
        }
    }
    if (collisionFound) {
        m_vertical_velocity = 0;
        m_position.y = bestY - m_frame_rec.height;
        return true;
    }
    return false;
}

auto Character::checkRightCollision(const std::vector<std::unique_ptr<Platform>> &platforms) -> bool {
    float characterRight = m_position.x + m_frame_rec.width;
    float characterTop = m_position.y;
    float headRegionHeight = m_frame_rec.height / constants::HEAD_REGION_DIVISOR;
    int collThreshold = constants::COLLISION_THRESHOLD;

    for (auto const &p: platforms) {
        float pt = p->getY();
        float pb = p->getY() + p->getTexture().height * p->getScale();
        if ((characterTop + headRegionHeight) < pt || characterTop > pb)
            continue;
        int collidingSamples = 0;
        for (int i = 0; i < constants::NUM_SAMPLES; ++i) {
            float sampleY = characterTop + i * (headRegionHeight / (constants::NUM_SAMPLES - 1));
            if (p->checkCollision({characterRight, sampleY})) {
                collidingSamples++;
            }
        }
        if (collidingSamples >= collThreshold)
            return true;
    }
    return false;
}

auto Character::checkTopCollision(const std::vector<std::unique_ptr<Platform>> &platforms) -> bool {
    float t = m_position.y;
    float l = m_position.x;
    float r = m_position.x + m_frame_rec.width;

    for (auto const &p: platforms) {
        if (r < p->getX() || l > p->getX() + p->getTexture().width * p->getScale()) {
            continue;
        }
        for (int i = 0; i < constants::NUM_SAMPLES; ++i) {
            float sampleX = l + i * (m_frame_rec.width / (constants::NUM_SAMPLES - 1));
            float offset = constants::TOP_SAMPLE_OFFSET;
            if (p->checkCollision({sampleX, t + offset})) {
                return true;
            }
        }
    }
    return false;
}
