#pragma once

#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>
#include "raylib.h"
#include "Background.h"
#include "Random.h"

// Forward declaration to avoid circular dependency
class Obstacle;

class Platform : public Background {
    static std::filesystem::path getRandomPlatformPath();

    // Flag to indicate if an obstacle has been spawned on this platform
    bool m_hasObstacle;
    // Unique pointer to the obstacle object
public:
    Platform(bool has_obstacle, float speed, float x, float y, float scale = 1.0f);

    ~Platform();

    // Update platform logic and update obstacle if present
    bool update();

    // Draw the platform and its obstacle (if exists)
    void draw();

    // Check collision with platform texture using per-pixel collision
    bool checkCollision(Vector2 point);

    [[nodiscard]] bool hasObstacle() const;

    // Access the obstacle pointer (could be null)
    Obstacle *get_obstacle() const;

    void changeSpeed(float speed);

    std::unique_ptr<Obstacle> m_obstacle;
    [[nodiscard]] inline const Texture2D &getTexture() const { return m_texture; }
    [[nodiscard]] inline float getScale() const { return m_scale; }

private:
    bool isOutsite();
};
