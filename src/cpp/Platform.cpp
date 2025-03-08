#include "../headers/Platform.h"
#include "../headers/Obstacle.h"

Platform::Platform(bool has_obstacle, float speed, float x, float y, float scale)
    : Background(getRandomPlatformPath(), speed, x, y, scale),
      m_hasObstacle{has_obstacle}
{
    if(m_hasObstacle) {
    	m_obstacle = std::make_unique<Obstacle>(*this, speed, scale);
    }
}

Platform::~Platform() {
    if (m_hasObstacle && m_obstacle) {
        m_obstacle.reset();
    }
    std::cout<<"Platform destroyed"<<std::endl;
}

bool Platform::update() {
    // Example: Move the platform to the left at the given speed.
    m_x -= m_speed;

    // Update the obstacle if one is present.
    if(m_hasObstacle && m_obstacle) {
        m_obstacle->update();
    }
    std::cout<<"Platform x: "<<m_x<<std::endl;
    // Return false when the platform has moved completely offscreen.
    return !isOutsite();
}


void Platform::draw() {
    // Draw the platform using the Background's draw method.
	Background::draw(m_x, m_y, 0.0f, 1.0f, WHITE);

    // Draw the obstacle if it exists.
    if(m_hasObstacle && m_obstacle) {
        m_obstacle->draw();
    }
}

bool Platform::hasObstacle() const {
    return m_hasObstacle;
}

bool Platform::checkCollision(Vector2 point) {
    // Translate global point to local platform coordinates
    float localX = point.x - m_x;
    float localY = point.y - m_y;

    // Compute the scaled dimensions of the texture
    int texWidth = static_cast<int>(m_texture.width * m_scale);
    int texHeight = static_cast<int>(m_texture.height * m_scale);

    // If the point lies outside the texture bounds, no collision
    if (localX < 0 || localY < 0 || localX >= texWidth || localY >= texHeight) {
        return false;
    }

    // Convert to pixel coordinates in the original image
    int pixelX = static_cast<int>(localX / m_scale);
    int pixelY = static_cast<int>(localY / m_scale);

    // Get the pixel color at this position
    Image img = LoadImageFromTexture(m_texture);
    Color pixel = GetImageColor(img, pixelX, pixelY);
    UnloadImage(img);

    // Check if the pixel is not transparent
    return pixel.a > 0;
}

bool Platform::isOutsite() {
    return m_x < -m_texture.width;
}


Obstacle* Platform::get_obstacle() const {
    return m_obstacle.get();
}

// Dummy implementation for getRandomPlatformPath.
// Ideally, this calls a function from Random.h/cpp to get a valid platform texture path.
std::filesystem::path Platform::getRandomPlatformPath() {
 	int randomIndex = Random::get(1, 5);
    return std::filesystem::path("resources/platforms/platform_" + std::to_string(randomIndex) + ".png");
}

void Platform::changeSpeed(float speed) {
    m_speed = speed;
	if(m_hasObstacle && m_obstacle) {
        m_obstacle->changeSpeed(speed);
    }
}