#include "../headers/Snow.hpp"
#include "../headers/Constants.hpp"
#include "../headers/DebugLog.hpp"

Snow::Snow(int count, int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight) {
    for (int i = 0; i < count; i++) {
        SnowParticle p;
        p.position = {static_cast<float>(GetRandomValue(0, m_screenWidth)),
                      static_cast<float>(GetRandomValue(0, m_screenHeight))};
        p.speed = static_cast<float>(GetRandomValue(constants::SNOW_MIN_SPEED, constants::SNOW_MAX_SPEED)) /
                  constants::SNOW_SPEED_DIVISOR;
        m_particles.push_back(p);
    }
}

auto Snow::update() -> void {
    for (auto &p: m_particles) {
        p.position.y += p.speed;
        if (p.position.y > m_screenHeight) {
            p.position.y = constants::SNOW_RESET_Y_OFFSET;
            p.position.x = static_cast<float>(GetRandomValue(0, m_screenWidth));
        }
    }
}

auto Snow::draw() -> void {
    for (auto &p: m_particles) {
        DrawCircleV(p.position, constants::SNOW_PARTICLE_RADIUS, Fade(WHITE, constants::SNOW_PARTICLE_ALPHA));
    }
}
