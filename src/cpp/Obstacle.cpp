#include "../headers/Obstacle.h"


Obstacle::Obstacle(const Platform &platform, float speed, int scale)
    : m_platform(platform), m_speed(speed), m_scale(scale)
{
    m_obstaclePath = getRandomObstaclePath();
    m_obstacle_image = LoadImage(m_obstaclePath.string().c_str());
    m_obstacle_texture = LoadTextureFromImage(m_obstacle_image);
    m_pixel_data = static_cast<Color*>(m_obstacle_image.data);

    // Load platform image to determine a valid starting point
    Image platformImg = LoadImageFromTexture(m_platform.getTexture());
    Color *platformPixels = LoadImageColors(platformImg);
    int pTexW = static_cast<int>(m_platform.getTexture().width * m_platform.getScale());
    int pTexH = static_cast<int>(m_platform.getTexture().height * m_platform.getScale());

    const int MAX_TRIES = 50;
    for (int i = 0; i < MAX_TRIES; i++) {
        float randX = Random::get(0.0f, static_cast<float>(pTexW));
        float randY = Random::get(0.0f, static_cast<float>(pTexH));
        int px = static_cast<int>(randX / m_platform.getScale());
        int py = static_cast<int>(randY / m_platform.getScale());
        if (px >= 0 && px < platformImg.width && py >= 0 && py < platformImg.height) {
            Color c = platformPixels[py * platformImg.width + px];
            if (c.a > 0) {
                m_obstacle_position.x = m_platform.getX() + randX - (m_obstacle_texture.width * m_scale * 0.5f);
                m_obstacle_position.y = m_platform.getY() + randY - (m_obstacle_texture.height * m_scale);
                break;
            }
        }
    }

    // Save the position relative to the platform
    m_relative_offset.x = m_obstacle_position.x - m_platform.getX();
    m_relative_offset.y = m_obstacle_position.y - m_platform.getY();

    UnloadImageColors(platformPixels);
    UnloadImage(platformImg);
}

Obstacle::~Obstacle() {
    UnloadTexture(m_obstacle_texture);
    UnloadImage(m_obstacle_image);
}

void Obstacle::update() {
    // Update the obstacle position so that it remains at the relative offset
    m_obstacle_position.x = m_platform.getX() + m_relative_offset.x;
    m_obstacle_position.y = m_platform.getY() + m_relative_offset.y;
    // Optionally update m_speed if needed; here we rely on platform movement.
}

void Obstacle::draw() {
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