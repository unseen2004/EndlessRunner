// Language: cpp
// File: `src/cpp/Snow.cpp`
#include "../headers/Snow.hpp"

Snow::Snow(int count, int screenWidth, int screenHeight)
    : m_screenWidth(screenWidth), m_screenHeight(screenHeight)
{
    for (int i = 0; i < count; i++) {
        SnowParticle p;
        p.position = { static_cast<float>(GetRandomValue(0, screenWidth)),
                       static_cast<float>(GetRandomValue(0, screenHeight)) };
        p.speed = static_cast<float>(GetRandomValue(50, 150)) / 100.0f; // speed between 0.5 and 1.5
        m_particles.push_back(p);
    }
}

void Snow::update() {
    for (auto &p : m_particles) {
        p.position.y += p.speed;
        if (p.position.y > m_screenHeight) {
            p.position.y = -3.0f; // reset above the screen
            p.position.x = static_cast<float>(GetRandomValue(0, m_screenWidth));
        }
    }
}

void Snow::draw() {
    for (auto &p : m_particles) {
        DrawCircleV(p.position, 3, Fade(WHITE, 0.8f));
    }
}