#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>
#include "raylib.h"
#include "Background.hpp"
#include "Random.hpp"

class Platform : public Background {
    static std::filesystem::path getRandomPlatformPath();

public:
    Platform(float speed, float x, float y, float scale = 1.0f);

    ~Platform();

    bool update();

    void draw();

    bool checkCollision(Vector2 point);

    void changeSpeed(float speed);

    [[nodiscard]] inline const Texture2D getTexture() const { return m_texture; }
    [[nodiscard]] inline float getScale() const { return m_scale; }

    void applyDashBoost(float dashBoost) {
        m_x -= dashBoost;
    }

private:
    bool isOutsite();

    Image m_cachedImage;
};

#endif // PLATFORM_HPP