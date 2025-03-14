#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <filesystem>
#include "raylib.h"
#include "Background.hpp"
#include "Random.hpp"

class Platform : public Background {
    static auto getRandomPlatformPath() -> std::filesystem::path;

public:
    Platform(float speed, float x, float y, float scale = 1.0f);

    ~Platform();

    auto update() -> bool;

    auto draw() -> void;

    auto checkCollision(const Vector2 &point) -> bool;

    auto changeSpeed(float speed) -> void;

    [[nodiscard]] inline auto getTexture() const -> Texture2D { return m_texture; }
    [[nodiscard]] inline auto getScale() const -> float { return m_scale; }
    auto applyDashBoost(float dashBoost) -> void { m_x -= dashBoost; }

private:
    auto isOutsite() -> bool;

    Image m_cachedImage;
};

#endif // PLATFORM_HPP
