#include "../headers/Cloud.h"


bool Cloud::update() {
    m_x -= m_speed * m_random_val;
    return m_x > -m_texture.width;
}

void Cloud::draw() {
    Background::draw(m_x, m_y, 0.0f, m_scale);
}
