#include "../headers/Platform.h"
#include "../headers/Obstacle.h"

Platform::Platform( float speed, float x, float y, float scale)
    : Background(getRandomPlatformPath(), speed, x, y, scale)
{
    m_cachedImage = LoadImageFromTexture(m_texture);
}



bool Platform::update() {
    // Example: Move the platform to the left at the given speed.
    m_x -= m_speed;

    // Return false when the platform has moved completely offscreen.
    return !isOutsite();
}

Platform::~Platform() {
    UnloadImage(m_cachedImage);
}

void Platform::draw() {
    // Draw the platform using the Background's draw method.
	Background::draw(m_x, m_y, 0.0f, 1.0f, WHITE);

}


// Language: cpp
// In src/cpp/Platform.cpp, update checkCollision():
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
    return pixel.a > 0;
}

bool Platform::isOutsite() {
    return m_x < -m_texture.width;
}



// Dummy implementation for getRandomPlatformPath.
// Ideally, this calls a function from Random.h/cpp to get a valid platform texture path.
std::filesystem::path Platform::getRandomPlatformPath() {
 	int randomIndex = Random::get(1, 5);
    return std::filesystem::path("resources/platforms/platform_" + std::to_string(randomIndex) + ".png");
}

void Platform::changeSpeed(float speed) {
    m_speed = speed;
}