#include "../headers/Obstacle.h"

Obstacle::Obstacle(const Platform& platform, float speed, int scale)
    : m_platform(platform) {
    std::filesystem::path obstacle_path = getRandomObstaclePath();
    if (obstacle_path.empty()) {
        throw std::logic_error("Obstacle file path cannot be empty");
    }

    // Load the obstacle texture
    m_obstacle_texture = LoadTexture(obstacle_path.string().c_str());

    // Set the obstacle position relative to the platform's position and size
    m_obstacle_position.x = platform.getX() + Random::get(0.0f, static_cast<float>(platform.getWidth() - m_obstacle_texture.width));
    m_obstacle_position.y = platform.getY(); // Ensure the obstacle is on the surface of the platform
    std::cout << "Obstacle created at: " << m_obstacle_position.x << ", " << m_obstacle_position.y << std::endl;//del
    m_speed = speed;
    m_scale = scale;
}

Obstacle::~Obstacle() {
    UnloadTexture(m_obstacle_texture);
    std::cout << "Obstacle destroyed" << std::endl;//del
}

void Obstacle::update() {
    m_obstacle_position.x -= m_speed;
}

void Obstacle::changeSpeed(float speed) {
    m_speed = speed;
}

void Obstacle::draw() {
    DrawTextureEx(m_obstacle_texture, m_obstacle_position, 0.0f, m_scale, WHITE);
}

std::filesystem::path Obstacle::getRandomObstaclePath() {
    int obstacleIndex = Random::get(1, 5);
    return std::filesystem::path("resources/rocks/rock_" + std::to_string(obstacleIndex) + ".PNG");
}