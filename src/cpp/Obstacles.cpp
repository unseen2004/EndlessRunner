#include "../headers/Obstacles.h"
#include "Random.h"

Obstacles::Obstacles()
    : Platform(std::filesystem::path("../resources/platforms/platform_5.png"), 0.2f, 0.0f, Random::get(100.0f, 550.0f)) {
    std::filesystem::path obstacle_path = getRandomObstaclePath();
    if (obstacle_path.empty()) {
        throw std::logic_error("Obstacle file path cannot be empty");
    }

    // Load the obstacle texture
    m_obstacle_texture = LoadTexture(obstacle_path.string().c_str());

    // Set the obstacle position relative to the platform's position and size
    m_obstacle_position.x = Random::get(0.0f, static_cast<float>(getWidth() - m_obstacle_texture.width));
    m_obstacle_position.y = m_y; // Ensure the obstacle is on the surface of the platform
}

Obstacles::~Obstacles() {
    UnloadTexture(m_obstacle_texture);
}

bool Obstacles::update() {
    if (Platform::update()) {
        m_obstacle_position.x -= m_speed;
        return true;
    }
    return false;
}

void Obstacles::draw() {
    Platform::draw();
    DrawTextureEx(m_obstacle_texture, m_obstacle_position, 0.0f, 4.0f, WHITE);
}

std::filesystem::path Obstacles::getRandomObstaclePath() {
    int obstacleIndex = Random::get(1, 4);
    return std::filesystem::path("../resources/rocks/rock_" + std::to_string(obstacleIndex) + ".PNG");
}