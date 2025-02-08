#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "Platform.h"
#include "raylib.h"
#include <filesystem>

class Obstacles : public Platform {
public:
    Obstacles();
    ~Obstacles();

    bool update();
    void draw();

private:
    Texture2D m_obstacle_texture;
    Vector2 m_obstacle_position;
    static std::filesystem::path getRandomObstaclePath();
};

#endif // OBSTACLES_HS_H