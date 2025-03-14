#ifndef SNOW_HPP
#define SNOW_HPP

#include <vector>
#include "raylib.h"

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

#endif // SNOW_HPP