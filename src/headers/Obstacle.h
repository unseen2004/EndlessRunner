#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <filesystem>
#include "raylib.h"
#include "Platform.h"
#include "Random.h"

class Obstacle {
public:
    Obstacle(const Platform& platform);
    ~Obstacle();

    void update();
    void draw();

private:
    Texture2D m_obstacle_texture;
    Vector2 m_obstacle_position;
    const Platform& m_platform;

    std::filesystem::path getRandomObstaclePath();
};

#endif // OBSTACLE_H