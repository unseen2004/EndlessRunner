#include "../headers/Character.h"

Character::Character(std::filesystem::path path1, std::filesystem::path path2, std::filesystem::path path3,
                     float speed, float x, float y, int currentFrame, int framesCounter, int framesSpeed,
                     int currentLine, bool is_jumping)
    : m_path_character(path1), m_path_explosion(path2), m_path_sound(path3), m_position{x, y},
      m_currentFrame(currentFrame), m_framesCounter(framesCounter), m_framesSpeed(framesSpeed),
      m_currentLine(currentLine), m_jumps_left(config::JUMPS_NUMBER)
{
    if (path1.empty() || path2.empty() || path3.empty()) {
        throw std::logic_error("File path cannot be empty");
    }
    m_character = LoadTexture(m_path_character.string().c_str());
    m_explosion = LoadTexture(m_path_explosion.string().c_str());
    m_boom = LoadSound(m_path_sound.string().c_str());
    m_frame_rec = {0.0f, 0.0f, (float)m_character.width / 6, (float)m_character.height};
}

Character::~Character() {
    UnloadTexture(m_character);
    UnloadTexture(m_explosion);
    UnloadSound(m_boom);
}

bool Character::update(bool input_jump, bool input_dash,
                         const std::vector<std::unique_ptr<Platform>> &bottomPlatforms,
                         const std::vector<std::unique_ptr<Platform>> &topPlatforms) {
    bool was_grounded = m_is_grounded;
    if (!m_is_jumping) {
        bool isGroundedBottom = checkGrounded(bottomPlatforms);
        bool isGroundedTop = checkGrounded(topPlatforms);
        m_is_grounded = isGroundedBottom || isGroundedTop;
    }
    if (!was_grounded && m_is_grounded) {
        m_jumps_left = config::JUMPS_NUMBER;
    }
    handleJump(input_jump);
    float dt = GetFrameTime();
    if (m_dash_cooldown_timer > 0)
        m_dash_cooldown_timer -= dt;
    handleDash(input_dash);
    if (!m_is_grounded)
        applyGravity();

    // Check for side/top collisions: if either occurs, mark character as dead.
    if (checkRightCollision(bottomPlatforms) || checkRightCollision(topPlatforms) ||
        checkTopCollision(bottomPlatforms) || checkTopCollision(topPlatforms)) {
        m_is_alive = false;
        return false;
    }

    m_position.y += m_vertical_velocity;
    if (m_is_grounded)
        run();
    else
        roll();
    if (m_position.y > config::SCREEN_HEIGHT) {
        m_is_alive = false;
        return false;
    }
    return true;
}

void Character::roll() {
    m_rotation += 10.0F;
}

Rectangle Character::getCollisionRect() const {
    // Return a rectangle based on m_position and the frame rectangle dimensions.
    Rectangle rec;
    rec.x = m_position.x;
    rec.y = m_position.y;
    rec.width = m_frame_rec.width;
    rec.height = m_frame_rec.height;
    return rec;
}
bool Character::checkObstacleCollision(const Obstacle &obstacle) const {
    Rectangle rec = this->getCollisionRect();
    const int numSamples = 3;
    for (int i = 0; i < numSamples; i++) {
        float sampleX = rec.x + (rec.width * i) / (numSamples - 1);
        float sampleY = rec.y + rec.height / 2;
        Vector2 samplePoint = { sampleX, sampleY };
        if (obstacle.checkCollision(samplePoint)) {
            return true;
        }
    }
    return false;
}
bool Character::checkGrounded(const std::vector<std::unique_ptr<Platform>>& platforms) {
    float character_bottom = m_position.y + m_frame_rec.height;
    float character_left = m_position.x;
    float character_right = m_position.x + m_frame_rec.width;
    const float scanRange = 10.0f;
    const float step = 1.0f;

    float bestCandidateY = std::numeric_limits<float>::max();
    bool collisionFound = false;

    for (const auto& platform : platforms) {
        if (character_right <= platform->getX() ||
            character_left >= platform->getX() + platform->getTexture().width * platform->getScale()) {
            continue;
        }
        const int numSamples = 5;
        for (int i = 0; i < numSamples; i++) {
            float sampleX = character_left + i * (m_frame_rec.width / (numSamples - 1));
            for (float offset = 0.0f; offset <= scanRange; offset += step) {
                Vector2 samplePoint = { sampleX, character_bottom + offset };
                if (platform->checkCollision(samplePoint)) {
                    float candidateY = samplePoint.y;
                    while (candidateY - step > character_bottom) {
                        Vector2 upwardSample = { sampleX, candidateY - step };
                        if (!platform->checkCollision(upwardSample)) break;
                        candidateY -= step;
                    }
                    if (candidateY < bestCandidateY) {
                        bestCandidateY = candidateY;
                    }
                    collisionFound = true;
                    break;
                }
            }
        }
    }

    if (collisionFound) {
        m_vertical_velocity = 0;
        m_position.y = bestCandidateY - m_frame_rec.height;
        return true;
    }
    return false;
}

void Character::applyGravity() {
    m_vertical_velocity += m_gravity;
    if (m_vertical_velocity > 15.0f) {
        m_vertical_velocity = 15.0f;
    }
}

void Character::handleJump(bool input_jump) {
    if (input_jump) {
        if ((m_is_grounded || m_jumps_left > 0) && !m_is_jumping) {
            if (!m_is_grounded) {
                m_jumps_left--;
            }
            m_is_jumping = true;
            m_jump_timer = 0.0f;
            m_vertical_velocity = m_jump_force;
        } else if (m_is_jumping && m_jump_timer < m_max_jump_time) {
            m_jump_timer += GetFrameTime();
            float jumpProgress = m_jump_timer / m_max_jump_time;
            float jumpFactor = 1.0f - jumpProgress;
            m_vertical_velocity = m_jump_force * jumpFactor;
        }
    } else {
        m_is_jumping = false;
    }
}

void Character::handleDash(bool input_dash) {
    float dt = GetFrameTime();
    // Only allow dash if cooldown is over
    if(input_dash && !m_is_dashing && m_dash_cooldown_timer <= 0.0f) {
        m_is_dashing = true;
        m_dash_timer = 0.0f;
        m_dash_cooldown_timer = m_max_dash_cooldown;
    }
    if(m_is_dashing) {
        m_dash_timer += dt;
        // Do not change character x position so that it remains fixed.
        if(m_dash_timer >= m_max_dash_time) {
            m_is_dashing = false;
        }
    }
}
// Increase the dash boost multiplier for more noticeable effect.
float Character::getDashBoost(float dt) const {
    // Multiply dt with a larger constant (e.g. 100) for testing.
    return m_is_dashing ? 1000.0f * dt : 0.0f;
}
void Character::run() {
    // Reset rotation when running so the character stays upright
    m_rotation = 0.0f;
    ++m_framesCounter;
    if (m_framesCounter > m_framesSpeed) {
        m_framesCounter = 0;
        ++m_currentFrame;
        if (m_currentFrame > 5) {
            m_currentFrame = 0;
        }
        m_frame_rec.x = (float)m_currentFrame * (float)m_character.width / 6.0f;
    }
}

void Character::draw() {
    // Draw character with rotation using DrawTexturePro.
    // Set the origin at the center of the frame so rotation occurs about the center.
    Vector2 origin = { m_frame_rec.width / 2.0f, m_frame_rec.height / 2.0f };
    Rectangle dest = { m_position.x + origin.x, m_position.y + origin.y, m_frame_rec.width, m_frame_rec.height };
    DrawTexturePro(m_character, m_frame_rec, dest, origin, m_rotation, WHITE);
}

void Character::changeSpeed(int speed) {
    if (speed > character_const::MAX_SPEED) {
        m_framesSpeed = 1;
    } else {
        m_framesSpeed = (character_const::MAX_SPEED - speed) - speed;
    }
}


// Language: cpp
bool Character::checkRightCollision(const std::vector<std::unique_ptr<Platform>> &platforms) {
    float characterRight = m_position.x + m_frame_rec.width;
    float characterTop = m_position.y;
    float headRegionHeight = m_frame_rec.height / 5.0f; // top 1/5 as head region
    const int numSamples = 5; // sample points in head region
    const int collisionThreshold = 1; // if one sample collides then head is touched

    for (const auto &platform : platforms) {
        float platformTop = platform->getY();
        float platformBottom = platform->getY() + platform->getTexture().height * platform->getScale();

        // Skip if there's no vertical overlap with the head region.
        if ( (characterTop + headRegionHeight) < platformTop || characterTop > platformBottom ) {
            continue;
        }

        int collidingSamples = 0;
        for (int i = 0; i < numSamples; i++) {
            float sampleY = characterTop + i * (headRegionHeight / (numSamples - 1));
            Vector2 samplePoint = { characterRight, sampleY };
            if (platform->checkCollision(samplePoint)) {
                collidingSamples++;
            }
        }
        if (collidingSamples >= collisionThreshold) {
            return true;
        }
    }
    return false;
}

bool Character::checkTopCollision(const std::vector<std::unique_ptr<Platform>> &platforms) {
    float characterTop = m_position.y;
    float characterLeft = m_position.x;
    float characterRight = m_position.x + m_frame_rec.width;
    const int numSamples = 5;
    // Use a small offset to sample above the character's top
    const float sampleOffset = -1.0f;

    for (const auto &platform : platforms) {
        // Check for horizontal overlap before sampling
        if (characterRight < platform->getX() ||
            characterLeft > platform->getX() + platform->getTexture().width * platform->getScale()) {
            continue;
        }
        for (int i = 0; i < numSamples; i++) {
            float sampleX = characterLeft + i * (m_frame_rec.width / (numSamples - 1));
            // Apply the offset so that the sampling point is slightly above the top edge.
            Vector2 samplePoint = { sampleX, characterTop + sampleOffset };
            if (platform->checkCollision(samplePoint)) {
                return true;
            }
        }
    }
    return false;
}