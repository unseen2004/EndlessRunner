#ifndef CLOUD_HPP
#define CLOUD_HPP

#include "Background.hpp"

class Cloud : public Background {
    float m_random_val;

public:
    Cloud(const std::filesystem::path &path, float speed, float random_val, float x, float y, float scale)
        : Background(path, speed, x, y, scale) {
        m_random_val = random_val;
    }

    void draw();

    bool update();

    void changeSpeed(float speed);

    void applyDashBoost(float dashBoost) {
        m_x -= dashBoost;
    }
};

#endif // CLOUD_HPP
