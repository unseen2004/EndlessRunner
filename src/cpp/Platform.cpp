#include "../headers/Platform.h"
#

void Platform::draw() {
    Background::draw(m_x, m_y, 0.0f, 1.0f, WHITE);
}

bool Platform::isOutsite() {
    return m_x < -this->m_texture.width;
}

bool Platform::update() {
    if (!isOutsite()) {
        m_x -= m_speed;
        return true;
    }
    return false;
}



Rectangle Platform::getBounds() const {
    return {m_x, m_y, static_cast<float>(m_texture.width), static_cast<float>(m_texture.height)};
}

bool Platform::isTouching(const Rectangle& other) {
    return CheckCollisionRecs(getBounds(), other);
}

bool Platform::touchLeft(const Rectangle& other) {
    Rectangle bounds = getBounds();
    return isTouching(other) && other.x + other.width <= bounds.x;
}

bool Platform::touchRight(const Rectangle& other) {
    Rectangle bounds = getBounds();
    return isTouching(other) && other.x >= bounds.x + bounds.width;
}

bool Platform::touchDown(const Rectangle& other) {
    Rectangle bounds = getBounds();
    return isTouching(other) && other.y >= bounds.y + bounds.height;
}

bool Platform::touchUp(const Rectangle& other) {
    Rectangle bounds = getBounds();
    return isTouching(other) && other.y + other.height <= bounds.y;
}

std::filesystem::path Platform::getRandomPlatformPath() {
    int platformIndex = Random::get(1, 5);
    return std::filesystem::path("../resources/platforms/platform_" + std::to_string(platformIndex) + ".png");
}