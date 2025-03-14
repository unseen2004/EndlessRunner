#ifndef CLOUD_HPP
#define CLOUD_HPP

#include "Background.hpp"

class Cloud : public Background {
    float m_random_val;

public:
    Cloud(const std::filesystem::path &path, float speed, float random_val, float x, float y, float scale) :
        Background(path, speed, x, y, scale), m_random_val(random_val) {}

    auto draw() -> void;

    auto update() -> bool;

    auto changeSpeed(float speed) -> void;

    auto applyDashBoost(float dashBoost) -> void { m_x -= dashBoost; }
};

#endif
