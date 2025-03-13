// Language: cpp
// File: `src/headers/Snow.h`
#pragma once
#include "raylib.h"
#include <vector>

struct SnowParticle {
    Vector2 position;
    float speed;
};

class Snow {
public:
    Snow(int count, int screenWidth, int screenHeight);

    void update();

    void draw();

private:
    int m_screenWidth;
    int m_screenHeight;
    std::vector<SnowParticle> m_particles;
};
