#include "../headers/Character.h"

Character::Character(std::filesystem::path path1, std::filesystem::path path2, std::filesystem::path path3,float speed ,float x,
                     float y, int currentFrame, int framesCounter, int framesSpeed, int currentLine, bool is_jumping)
    : m_path_character(path1), m_path_explosion(path2), m_path_sound(path3), m_position{x, y},
      m_currentFrame(currentFrame), m_framesCounter(framesCounter), m_framesSpeed(framesSpeed),
      m_currentLine(currentLine), m_jumps_left(config::JUMPS_NUMBER) {
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
                      const std::vector<std::unique_ptr<Platform>>& bottomPlatforms,
                      const std::vector<std::unique_ptr<Platform>>& topPlatforms) {
    bool was_grounded = m_is_grounded;
    // Only check grounded if not currently jumping
    if (!m_is_jumping) {
        m_is_grounded = checkGrounded(bottomPlatforms);
    }

    // Reset jump count when landing
    if (!was_grounded && m_is_grounded) {
        m_jumps_left = config::JUMPS_NUMBER;
    }

    // Process jump input regardless of grounded status
    handleJump(input_jump);

    // Gravity applies whenever not grounded
    if (!m_is_grounded) {
        applyGravity();
    }

    // Update vertical position
    m_position.y += m_vertical_velocity;

    // Animate if on ground
    if (m_is_grounded) {
        run();
    }

    if (m_position.y > config::SCREEN_HEIGHT) {
        m_is_alive = false;
        return false;
    }

    return true;
}



bool Character::checkGrounded(const std::vector<std::unique_ptr<Platform>>& platforms) {
    float character_bottom = m_position.y + m_frame_rec.height;
    float character_left = m_position.x;
    float character_right = m_position.x + m_frame_rec.width;
    const float scanRange = 10.0f;
    const float step = 1.0f;

    // Use a high initial value as we want to find the top-most (smallest y) collision
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
            // Scan downward from the character's feet to find a collision pixel
            for (float offset = 0.0f; offset <= scanRange; offset += step) {
                Vector2 samplePoint = { sampleX, character_bottom + offset };
                if (platform->checkCollision(samplePoint)) {
                    // Once a collision is found, scan upward to get the top-most collision pixel.
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
                    break; // Exit vertical scan for this sample point
                }
            }
        }
    }

    if (collisionFound) {
        // Position the character so that its feet align with the top-most collision pixel.
        m_vertical_velocity = 0;
        m_position.y = bestCandidateY - m_frame_rec.height;
        return true;
    }
    return false;
}

void Character::applyGravity() {
    m_vertical_velocity += m_gravity;

    // Cap falling speed
    if (m_vertical_velocity > 15.0f) {
        m_vertical_velocity = 15.0f;
    }
}

void Character::handleJump(bool input_jump) {
    if (input_jump) {
        // Start jump logic
        if ((m_is_grounded || m_jumps_left > 0) && !m_is_jumping) {
            // Start new jump (existing code)
            if (!m_is_grounded) {
                m_jumps_left--;
            }
            m_is_jumping = true;
            m_jump_timer = 0.0f;
            m_vertical_velocity = m_jump_force;
        }
        // Continue jump while button held
        else if (m_is_jumping && m_jump_timer < m_max_jump_time) {
            m_jump_timer += GetFrameTime();
            // Apply continued upward force with gradual decrease
            float jumpProgress = m_jump_timer / m_max_jump_time;
            float jumpFactor = 1.0f - jumpProgress;
            m_vertical_velocity = m_jump_force * jumpFactor;
        }
    } else {
        // Button released, end jump
        m_is_jumping = false;
    }
}

void Character::draw() {
    DrawTextureRec(m_character, m_frame_rec, m_position, WHITE);
}



void Character::run() {
    ++m_framesCounter;
    if (m_framesCounter > m_framesSpeed) {
        m_framesCounter = 0;
        ++m_currentFrame;
        if (m_currentFrame > 5) {
            m_currentFrame = 0;
        }
        m_frame_rec.x = (float)m_currentFrame * (float)m_character.width / 6;
    }
}



void Character::changeSpeed(int speed) {
    if(speed > character_const::MAX_SPEED){
        m_framesSpeed = 1;
    }else{
    m_framesSpeed = (character_const::MAX_SPEED - speed) - speed;
}}

