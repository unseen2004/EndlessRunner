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

    // Dash accessors
    bool isDashing() const { return m_is_dashing; }
    float getDashBoost(float dt) const { return m_is_dashing ? m_dash_speed * dt : 0.0f; }

private:
    float m_vertical_velocity{0.0f};
    bool m_is_grounded{true};
    float m_jump_timer{0.0f};
    float m_max_jump_time{0.6f};
    float m_jump_force{config::BASE_JUMP_FORCE};
    int m_jumps_left{config::JUMPS_NUMBER};
    float m_gravity{config::BASE_GRAVITY};

    // Dash variables
    bool m_is_dashing{false};
    float m_dash_timer{0.0f};
    const float m_max_dash_time{0.2f};
    const float m_dash_speed{10.0f};
    // New cooldown variables
    float m_dash_cooldown_timer{0.0f};
    const float m_max_dash_cooldown{1.0f};

public:
    bool checkGrounded(const std::vector<std::unique_ptr<Platform> > &platforms);

    void applyGravity();

    void handleJump(bool input_jump);

    // Updated dash handling method; no longer moves m_position.x but triggers dash state
    void handleDash(bool input_dash);

    bool isAlive() const { return m_is_alive; }
};

#endif // CHARACTER_H
