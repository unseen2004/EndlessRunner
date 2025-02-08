#include "../headers/Cloud.h"

bool Cloud::update() {
    m_x -= m_speed;
    return m_x > 0;
}

void Cloud::draw() {
    Background::draw(m_x, m_y, 0.0f, m_scale);
}