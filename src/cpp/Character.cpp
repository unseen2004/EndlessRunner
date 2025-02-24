#include "../headers/Character.h"

Character::Character(std::filesystem::path path1, std::filesystem::path path2, std::filesystem::path path3, float x,
                     float y, int currentFrame, int framesCounter, int framesSpeed, int currentLine, bool is_jumping)
    : m_path_character(path1), m_path_explosion(path2), m_path_sound(path3), m_position{x, y},
      m_currentFrame(currentFrame), m_framesCounter(framesCounter), m_framesSpeed(framesSpeed),
      m_currentLine(currentLine), m_jumps_left(config::JUMPS_NUMBER), m_is_jumping(is_jumping) {
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

void Character::run() {
    ++m_framesCounter;
    if (m_framesCounter >= config::FRAMES / m_framesSpeed) {
        m_framesCounter = 0;
        ++m_currentFrame;
        if (m_currentFrame > 5) {
            m_currentFrame = 0;
        }
        m_frame_rec.x = (float)m_currentFrame * (float)m_character.width / 6;
    }
    DrawTextureRec(m_character, m_frame_rec, m_position, WHITE);
}

void Character::die() {
    InitAudioDevice();
    float frameWidth = (float)(m_explosion.width / character_const::NUM_FRAMES_PER_LINE);
    float frameHeight = (float)(m_explosion.height / character_const::NUM_LINES);

    m_currentFrame = 0;
    m_currentLine = 0;
    m_framesCounter = 0;

    Rectangle frameRec = {0, 0, frameWidth, frameHeight};
    m_position.x -= frameWidth / 2.0f;
    m_position.y -= frameHeight / 2.0f;
    bool active{true};
    PlaySound(m_boom);

    ++m_framesCounter;
    while (active) {
        if (m_framesCounter > 2) {
            ++m_currentFrame;

            if (m_currentFrame >= character_const::NUM_FRAMES_PER_LINE) {
                m_currentFrame = 0;
                ++m_currentLine;

                if (m_currentLine >= character_const::NUM_LINES) {
                    m_currentLine = 0;
                    active = false;
                }
            }

            m_framesCounter = 0;
        }

        frameRec.x = frameWidth * m_currentFrame;
        frameRec.y = frameHeight * m_currentLine;

        DrawTextureRec(m_explosion, frameRec, m_position, WHITE);
    }
}

bool Character::init_jump() {
    if (m_jumps_left < 1) {
        return false;
    }
    --m_jumps_left;
    m_is_jumping = true;
    m_framesCounter = 0;
    m_currentFrame = 0;
    return true;
}

void Character::jump() {
    if (!m_is_jumping) return;

    ++m_framesCounter;
    if (m_framesCounter >= config::FRAMES / m_framesSpeed) {
        m_framesCounter = 0;
        ++m_currentFrame;
        if (m_currentFrame > 5) {
            m_currentFrame = 0;
            m_is_jumping = false;
            m_jumps_left = config::JUMPS_NUMBER; // Reset jumps left after jump ends
        }
        m_frame_rec.x = (float)m_currentFrame * (float)m_character.width / 6;
    }

    // Move character up
    m_position.y -= 5.0f; // Adjust the speed as needed

    DrawTextureRec(m_character, m_frame_rec, m_position, WHITE);
}

void Character::dash() {
    // TO DO: Implement dash logic
}

void Character::changeSpeed(int n) {
    m_framesSpeed += n;
    if (m_framesSpeed > config::MAX_FRAME_SPEED) m_framesSpeed = config::MAX_FRAME_SPEED;
    else if (m_framesSpeed < config::MIN_FRAME_SPEED) m_framesSpeed = config::MIN_FRAME_SPEED;
}

void Character::newSpeed(int n) {
    m_framesSpeed = n;
    if (m_framesSpeed > config::MAX_FRAME_SPEED) m_framesSpeed = config::MAX_FRAME_SPEED;
    else if (m_framesSpeed < config::MIN_FRAME_SPEED) m_framesSpeed = config::MIN_FRAME_SPEED;
}
