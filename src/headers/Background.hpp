#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP
#include <filesystem>
#include "raylib.h"

class Background {
protected:
    float m_x;
    float m_y;
    float m_speed;
    float m_scale;
    Texture2D m_texture;
    std::filesystem::path m_texturePath;

public:
    explicit Background(const std::filesystem::path &path, float speed = 0.1F, float x = 0.0f, float y = 0.0f,
                        float scale = 2.0f) noexcept;

    ~Background() noexcept;

    auto resetIfOutsite() -> void;

    auto draw(float x = 0.0f, float y = 0.0f, float rotation = 0.0f, float scale = 2.0f, Color color = WHITE) -> void;

    [[nodiscard]] auto getX() const -> float;

    [[nodiscard]] auto getY() const -> float;

    auto changeSpeed(float speed) -> void;

    [[nodiscard]] auto getWidth() const -> int;

    auto update() -> void;

    auto applyDashBoost(float dashBoost) -> void { m_x -= dashBoost; }
};

#endif
