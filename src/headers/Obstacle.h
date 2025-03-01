#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <filesystem>
#include "raylib.h"
#include "Platform.h"
#include "Random.h"
#include <iostream> //del

class Obstacle {
public:
    Obstacle(const Platform& platform, float speed, int m_scale);
    ~Obstacle();

    void update();
    void draw();
    void changeSpeed(float speed);

private:
    Texture2D m_obstacle_texture;
    Vector2 m_obstacle_position;
    const Platform& m_platform;
    float m_speed;
    int m_scale;

    std::filesystem::path getRandomObstaclePath();
};

#endif // OBSTACLE_H