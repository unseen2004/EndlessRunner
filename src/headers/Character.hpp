#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <filesystem>
#include <vector>
#include "Config.hpp"
#include "Platform.hpp"
#include "raylib.h"

namespace character_const {
    constexpr int NUM_FRAMES_PER_LINE = 5;
    constexpr int NUM_LINES = 5;
    constexpr int MAX_SPEED = 10;
    constexpr int GRAVITY = 1;
}; // namespace character_const

class Character {
public:
    Character(std::filesystem::path path1, float speed = 0.1F, float x = config::CHARACTER_START_X, float y = 0.0f,
              int currentFrame = 0, int framesCounter = 0, int framesSpeed = 8, int currentLine = 0,
              bool is_jumping = false);

    ~Character();

    auto update(bool input_jump, bool input_dash, const std::vector<std::unique_ptr<Platform>> &bottomPlatforms,
                const std::vector<std::unique_ptr<Platform>> &topPlatforms) -> bool;

    auto draw() -> void;

    auto changeSpeed(int speed) -> void;

    [[nodiscard]] auto isDashing() const -> bool { return m_is_dashing; }

    auto getDashBoost(float dt) const -> float;

    auto getCollisionRect() const -> Rectangle;

    auto applyGravity() -> void;

    auto isDeadAnimationFinished() const -> bool { return m_deadAnimationFinished; }

    auto updateDeadAnimation() -> void;

    auto handleJump(bool input_jump) -> void;

    auto handleDash(bool input_dash) -> void;

    [[nodiscard]] auto isAlive() const -> bool { return m_is_alive; }
    auto kill() -> void { m_is_alive = false; }

private:
    auto run() -> void;

    auto roll() -> void;

    auto checkGrounded(const std::vector<std::unique_ptr<Platform>> &platforms) -> bool;

    auto checkRightCollision(const std::vector<std::unique_ptr<Platform>> &platforms) -> bool;

    auto checkTopCollision(const std::vector<std::unique_ptr<Platform>> &platforms) -> bool;

    Vector2 m_position;
    int m_currentFrame;
    int m_framesCounter;
    int m_framesSpeed;
    int m_currentLine;
    bool m_is_jumping{false};
    Texture2D m_character;
    Texture2D m_explosion;
    Sound m_boom;
    std::filesystem::path m_path_character;
    std::filesystem::path m_path_explosion;
    std::filesystem::path m_path_sound;
    Rectangle m_frame_rec;
    float m_speed;
    bool m_is_alive{true};
    float m_vertical_velocity{0.0F};
    bool m_is_grounded{true};
    float m_jump_timer{0.0F};
    float m_max_jump_time{0.6F};
    float m_jump_force{config::BASE_JUMP_FORCE};
    int m_jumps_left{config::JUMPS_NUMBER};
    float m_gravity{config::BASE_GRAVITY};
    bool m_is_dashing{false};
    float m_dash_timer{0.0F};
    const float m_max_dash_time{0.2F};
    const float m_dash_speed{10.0F};
    float m_dash_cooldown_timer{0.0F};
    const float m_max_dash_cooldown{1.0F};
    float m_rotation{0.0F};
    int m_explosionCurrentFrame{0};
    int m_explosionCurrentLine{0};
    int m_explosionFramesCounter{0};
    bool m_deadAnimationFinished{false};
};

#endif
