#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <filesystem>
#include <vector>
#include "raylib.h"
#include "Config.h"
#include "Platform.h"


namespace character_const {
    constexpr int NUM_FRAMES_PER_LINE = 5;
    constexpr int NUM_LINES = 5;
    constexpr int MAX_SPEED = 10;
    constexpr int GRAVITY = 1;
};

class Character {
    Vector2 m_position;
    int m_currentFrame;
    int m_framesCounter;
    int m_framesSpeed;
    bool m_is_jumping{false};
    int m_currentLine;
    Texture2D m_character;
    Texture2D m_explosion;
    Sound m_boom;
    std::filesystem::path m_path_character;
    std::filesystem::path m_path_explosion;
    std::filesystem::path m_path_sound;
    Rectangle m_frame_rec;
    float m_speed{1};
    bool m_input_jump{};
    bool m_input_dash{};
    bool m_is_alive{true};
    int m_prev_jump{};

public:
    Character(std::filesystem::path path1, std::filesystem::path path2, std::filesystem::path path3,
              float m_speed = 0.1f, float x = config::CHARACTER_START_X,
              float y = 0, int currentFrame = 0, int framesCounter = 0,
              int framesSpeed = 8, int currentLine = 0, bool is_jumping = false);

    ~Character();

private:
    void run();

public:
    bool update(bool input_jump, bool input_dash, const std::vector<std::unique_ptr<Platform> > &bottomPlatforms,
                const std::vector<std::unique_ptr<Platform> > &topPlatforms);

    void draw();

    void changeSpeed(int n);

    // Add to Character.h
private:
    float m_vertical_velocity{0.0f};
    bool m_is_grounded{true};
    float m_jump_timer{0.0f};
    float m_max_jump_time{0.6f};
    float m_jump_force{config::BASE_JUMP_FORCE};
    int m_jumps_left{config::JUMPS_NUMBER};
    float m_gravity{config::BASE_GRAVITY};

public:
    // Add new method declarations
    bool checkGrounded(const std::vector<std::unique_ptr<Platform> > &platforms);

    void applyGravity();

    void handleJump(bool input_jump);

    bool isAlive() const { return m_is_alive; }
};

#endif // CHARACTER_H
