// Programming language: cpp
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <filesystem>
#include "raylib.h"
#include "Random.h"
#include "Platform.h"
#include "Config.h"

class Obstacle {
    const Platform &m_platform;
    Texture2D m_obstacle_texture;
    Vector2 m_obstacle_position{0, 0};
    Vector2 m_relative_offset{0, 0}; // Relative offset from platform position
    float m_speed;
    float m_scale;
    std::filesystem::path m_obstaclePath;
    Image m_obstacle_image;
    Color *m_pixel_data = nullptr;
public:
    Obstacle(const Platform &platform, float speed, int scale);
    ~Obstacle();
    void update();
    void draw();
    void changeSpeed(float speed);
    bool checkCollision(Vector2 point);
private:
    std::filesystem::path getRandomObstaclePath();
};

#endif // OBSTACLE_H
