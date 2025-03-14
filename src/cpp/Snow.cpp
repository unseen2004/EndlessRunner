#include "../headers/Snow.hpp"
#include "../headers/Constants.hpp"
#include "../headers/DebugLog.hpp"

Snow::Snow(int count, int screenWidth, int screenHeight)
    : m_screenWidth(screenWidth), m_screenHeight(screenHeight)
{
    LOG("Creating snow system with " << count << " particles");
    for (int i = 0; i < count; i++) {
        SnowParticle p;
        p.position = {
            static_cast<float>(GetRandomValue(0, screenWidth)),
            static_cast<float>(GetRandomValue(0, screenHeight))
        };
        p.speed = static_cast<float>(GetRandomValue(
            constants::SNOW_MIN_SPEED,
            constants::SNOW_MAX_SPEED)) /
            constants::SNOW_SPEED_DIVISOR; // speed between 0.5 and 1.5
        m_particles.push_back(p);
    }
}

void Snow::update() {
    for (auto &p : m_particles) {
        p.position.y += p.speed;
        if (p.position.y > m_screenHeight) {
            p.position.y = constants::SNOW_RESET_Y_OFFSET; // reset above the screen
            p.position.x = static_cast<float>(GetRandomValue(0, m_screenWidth));
        }
    }
}

void Snow::draw() {
    for (auto &p : m_particles) {
        DrawCircleV(p.position, constants::SNOW_PARTICLE_RADIUS,
                   Fade(WHITE, constants::SNOW_PARTICLE_ALPHA));
    }
}