#include "../headers/Background.hpp"
#include "../headers/Constants.hpp"
#include <stdexcept>

Background::Background(const std::filesystem::path& path,
                       float speed,
                       float x,
                       float y,
                       float scale) noexcept
    : m_x(x), m_y(y), m_speed(speed), m_scale(scale), m_texturePath(path) {
    m_texture = LoadTexture(m_texturePath.string().c_str());
}

Background::~Background() noexcept {
    UnloadTexture(m_texture);
}

auto Background::resetIfOutsite() -> void {
    if (m_x <= -m_texture.width * constants::BACKGROUND_WIDTH_MULTIPLIER)
        m_x = 0;
}

auto Background::draw(float x, float y, float rotation, float scale, Color color) -> void {
    DrawTextureEx(m_texture, { x, y }, rotation, scale, color);
}

auto Background::getX() const -> float {
    return m_x;
}

auto Background::getY() const -> float {
    return m_y;
}

auto Background::changeSpeed(float speed) -> void {
    m_speed = speed;
}

auto Background::getWidth() const -> int {
    return m_texture.width;
}

auto Background::update() -> void {
    m_x -= m_speed;
    resetIfOutsite();
}
