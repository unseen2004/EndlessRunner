#pragma once

#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>
#include "raylib.h"
#include "Background.h"
#include "Random.h"


class Platform : public Background {
    static std::filesystem::path getRandomPlatformPath();

    // Flag to indicate if an obstacle has been spawned on this platform
    // Unique pointer to the obstacle object
public:
    Platform(float speed, float x, float y, float scale = 1.0f);

    ~Platform();

    // Update platform logic and update obstacle if present
    bool update();

    // Draw the platform and its obstacle (if exists)
    void draw();

    // Check collision with platform texture using per-pixel collision
    bool checkCollision(Vector2 point);


    // Access the obstacle pointer (could be null)

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
