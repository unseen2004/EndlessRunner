#include "../headers/Background.h"

Background::Background(const std::filesystem::path& path, float speed, float x, float y, float scale)
    : m_speed(speed), m_x(x), m_y(y), m_scale(scale), m_texturePath(path) {
    if (path.empty()) {
        throw std::logic_error("File path cannot be empty");
    }
    m_texture = LoadTexture(m_texturePath.string().c_str());
}

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

float Background::getY() const {
    return m_y;
}

void Background::changeSpeed(const float speed) {
    m_speed = speed;
}

int Background::getWidth() const {
    return m_texture.width;
}

void Background::update() {
  	m_x -= m_speed ;
    resetIfOutsite();
}

