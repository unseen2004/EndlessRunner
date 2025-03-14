#include "../headers/Platform.hpp"
#include "../headers/Constants.hpp"
#include "../headers/DebugLog.hpp"

Platform::Platform(float speed, float x, float y, float scale)
    : Background(getRandomPlatformPath(), speed, x, y, scale)
{
    m_cachedImage = LoadImageFromTexture(m_texture);
    LOG("Platform created at position (" << x << ", " << y << ") with scale " << scale);
}

bool Platform::update() {
    // Move the platform to the left at the given speed.
    m_x -= m_speed;
    LOG("Platform at position (" << m_x << ", " << m_y << ")");

    // Return false when the platform has moved completely offscreen.
    return !isOutsite();
}

Platform::~Platform() {
    UnloadImage(m_cachedImage);
    LOG("Platform destroyed");
}

void Platform::draw() {
    // Draw the platform using the Background's draw method.
    Background::draw(m_x, m_y, constants::PLATFORM_ROTATION, m_scale, WHITE);
}

bool Platform::checkCollision(Vector2 point) {
    // Translate global point to local platform coordinates
    float localX = point.x - m_x;
    float localY = point.y - m_y;

    // Compute the scaled dimensions of the texture
    int texWidth = static_cast<int>(m_texture.width * m_scale);
    int texHeight = static_cast<int>(m_texture.height * m_scale);

    if (localX < 0 || localY < 0 || localX >= texWidth || localY >= texHeight) {
        return false;
    }

    // Convert to pixel coordinates in the original image
    int pixelX = static_cast<int>(localX / m_scale);
    int pixelY = static_cast<int>(localY / m_scale);
    // Use the cached image for pixel collision
    Color pixel = GetImageColor(m_cachedImage, pixelX, pixelY);
    LOG("Platform collision check at local point (" << pixelX << ", " << pixelY << "), alpha: " << (int)pixel.a);
    return pixel.a > 0;
}

bool Platform::isOutsite() {
    bool result = m_x < -m_texture.width;
    if (result) {
        LOG("Platform is now outside screen");
    }
    return result;
}

std::filesystem::path Platform::getRandomPlatformPath() {
    int randomIndex = Random::get(constants::MIN_PLATFORM_TYPE, constants::MAX_PLATFORM_TYPE);
    std::string path = "resources/platforms/platform_" + std::to_string(randomIndex) + ".png";
    LOG("Selected random platform path: " << path);
    return std::filesystem::path(path);
}

void Platform::changeSpeed(float speed) {
    LOG("Platform speed changed from " << m_speed << " to " << speed);
    m_speed = speed;
}