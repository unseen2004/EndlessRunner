#include "../headers/Obstacle.h"

#include "../headers/Obstacle.h"

Obstacle::Obstacle(const Platform &platform, float speed, int scale)
    : m_platform(platform), m_speed(speed), m_scale(scale)
{
    // Load the obstacle image and its texture.
    m_obstaclePath = getRandomObstaclePath();
    m_obstacle_image = LoadImage(m_obstaclePath.string().c_str());
    m_obstacle_texture = LoadTextureFromImage(m_obstacle_image);

    // For per-pixel collision checking, assume that the image's pixel data is in m_obstacle_image.data.
    m_pixel_data = static_cast<Color*>(m_obstacle_image.data);

    // Calculate the available horizontal space on the platform.
    float platformX = m_platform.getX();
    float platformWidth = static_cast<float>(m_platform.getWidth());
    float obstacleWidth = m_obstacle_texture.width * m_scale;
    // Randomly choose an offset ensuring the obstacle stays fully within the platform's width.
    float randomOffset = Random::get(0.0f, platformWidth - obstacleWidth);
    m_obstacle_position.x = platformX + randomOffset;

    // Place the obstacle on the platform surface.
    m_obstacle_position.y = m_platform.getY() - (m_obstacle_texture.height * m_scale);
    std::cout << "Obstacle created at: " << m_obstacle_position.x << ", " << m_obstacle_position.y << std::endl;
}

Obstacle::~Obstacle() {
    // Free resources.
    UnloadTexture(m_obstacle_texture);
    UnloadImage(m_obstacle_image);
    // m_pixel_data is part of m_obstacle_image and does not need separate cleanup.
    std::cout << "Obstacle destroyed" << std::endl;
}

void Obstacle::update() {
    // Update the obstacle position (e.g., moving with the platform's speed).
    m_obstacle_position.x -= m_speed;
}

void Obstacle::draw() {
    // Render the obstacle.
    DrawTextureEx(m_obstacle_texture, m_obstacle_position, 0.0f, m_scale, WHITE);
}

void Obstacle::changeSpeed(float speed) {
    m_speed = speed;
}

bool Obstacle::checkCollision(Vector2 point) {
    // Convert the global point to local obstacle coordinates
    float localX = point.x - m_obstacle_position.x;
    float localY = point.y - m_obstacle_position.y;

    // Calculate scaled dimensions
    int texWidth = static_cast<int>(m_obstacle_texture.width * m_scale);
    int texHeight = static_cast<int>(m_obstacle_texture.height * m_scale);

    // Check bounds first
    if (localX < 0 || localY < 0 || localX >= texWidth || localY >= texHeight) {
        return false;
    }

    // Convert to pixel coordinates in the original image
    int pixelX = static_cast<int>(localX / m_scale);
    int pixelY = static_cast<int>(localY / m_scale);

    // Bounds check for the image coordinates
    if (pixelX < 0 || pixelY < 0 ||
        pixelX >= m_obstacle_image.width || pixelY >= m_obstacle_image.height) {
        return false;
    }

    // Get the pixel color
    int index = pixelY * m_obstacle_image.width + pixelX;
    Color pixelColor = m_pixel_data[index];

    // Return true if pixel is not transparent
    return pixelColor.a > 0;
}

std::filesystem::path Obstacle::getRandomObstaclePath() {
    int obstacleIdx = Random::get(1, 5);
    return std::filesystem::path("resources/rocks/rock_" + std::to_string(obstacleIdx) + ".PNG");
}