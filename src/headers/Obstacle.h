#pragma once

#include <filesystem>
#include "raylib.h"
#include "Random.h"
#include "Platform.h"
#include "Config.h"

class Obstacle {

    const Platform &m_platform;
    Texture2D m_obstacle_texture;
    Vector2 m_obstacle_position{0, 0};
    float m_speed;
    float m_scale;
    std::filesystem::path m_obstaclePath;
    Image m_obstacle_image;
    Color *m_pixel_data = nullptr;
public:
    Obstacle(const Platform &platform, float speed, int scale);

    ~Obstacle();

    // Update obstacle logic (e.g. movement)
    void update();

    // Draw the obstacle using the texture and applied scaling.
    void draw();

    // Change the movement speed of the obstacle
    void changeSpeed(float speed);

    // Check collision with the obstacle texture using per-pixel collision
    bool checkCollision(Vector2 point);

private:
    std::filesystem::path getRandomObstaclePath();
};
