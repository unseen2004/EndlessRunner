#include "../headers/Cloud.hpp"

auto Cloud::update() -> bool {
    m_x -= m_speed * m_random_val;
    return m_x > -m_texture.width;
}

auto Cloud::draw() -> void {
    Background::draw(m_x, m_y, 0.0f, m_scale);
}

auto Cloud::changeSpeed(float speed) -> void {
    m_speed = speed;
}