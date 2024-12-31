#include "headers/all_horizontal_movable.h"

Background::Background(const char *path, float x, float y, float speed)
    : m_x(x), m_y(y), m_texture(LoadTexture(path)) {m_speed = speed;}

Background::~Background() {
    UnloadTexture(m_texture);
}

void Background::resetIfOutsite() {
    if (m_x <= -m_texture.width * 2)
        m_x = 0;
}

void Background::draw(float x, float y, float rotation, float scale, Color color) {
    DrawTextureEx(m_texture, (Vector2){x, y}, rotation, scale, color);
}

float Background::getX() const {
    return m_x;
}

void Background::changeX(const float x) {
    m_x += x;
}

int Background::getWidth() const {
    return m_texture.width;
}

