#include "headers/all_horizontal_movable.h"
#include "headers/config.h"

Background::Background(const std::filesystem::path& path, float speed, float x, float y, float scale)
    :m_speed(speed), m_x(x), m_y(y), m_texturePath(path) {
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
    m_speed += speed;
}

int Background::getWidth() const {
    return m_texture.width;
}
void Background::update(){
    m_x -= m_speed;
    resetIfOutsite();
}

bool Cloud::update() {
    m_x -= m_speed;

    return m_x > 0;
}

    void Cloud::draw() {
        Background::draw(m_x, m_y, 0.0f, m_scale);
    }

void Platform::draw()
{
    Background::draw(m_x, m_y, 0.0f, 1.0f, WHITE);
}

bool Platform::isOutsite(){
         return m_x < -config::PLATFORM_WIDTH;
  }

 bool Platform::update(){
   if(!isOutsite()){
		m_x -= m_speed;
                return true;
     }
return false;
   }
// delte y and add random number
bool Platform::resetIfOutsite() {
	if(!isOutsite()){
          return false;
     }

     m_x = config::SCREENWIDTH + config::PLATFORM_WIDTH;
     m_y = Random::get(100.0f, 550.0f);
     return true;
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

std::filesystem::path Obstacles::getRandomObstaclePath() {
    int obstacleIndex = Random::get(1, 4);
    return std::filesystem::path("../resources/rocks/rock_" + std::to_string(obstacleIndex) + ".PNG");
}


// getRandomPlatformPath,     static std::filesystem::path getRandomPlatformPath();
    static std::filesystem::path getRandomObstaclePath();
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
    if(Platform::update()){
      	m_obstacle_position.x -= m_speed;
   		return true;
      }
      return false;
}

void Obstacles::draw() {
    Platform::draw();
    DrawTextureEx(m_obstacle_texture, (Vector2){m_obstacle_position.x, m_obstacle_position.y},0.0f, 4.0f, WHITE);
}