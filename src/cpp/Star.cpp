#include "../headers/Star.hpp"
#include "../headers/Constants.hpp"
#include "../headers/DebugLog.hpp"

int Star::s_collectedStars = 0;

Star::Star(Vector2 position)
    : m_position(position), m_numFrames(constants::STAR_FRAMES), m_currentFrame(0),
      m_animationTimer(0.0f), m_animationInterval(constants::STAR_ANIMATION_INTERVAL),
      m_collected(false), m_scale(constants::STAR_SCALE), m_speed(0.0f),
      m_rotation(0.0f), m_spinSpeed(0.0f) {
    m_texture = LoadTexture("../resources/star.png");
    m_frameRec.x = 0;
    m_frameRec.y = 0;
    m_frameRec.width = m_texture.width / m_numFrames;
    m_frameRec.height = m_texture.height;
}

Star::~Star() {
    UnloadTexture(m_texture);
}

auto Star::update() -> void {
    applyMovement(m_speed);
}

auto Star::changeSpeed(float n) -> void {
    m_speed = n;
}

auto Star::draw() -> void {
    DrawTextureEx(m_texture, m_position, constants::STAR_ROTATION, m_scale, WHITE);
}

auto Star::getBoundingBox() const -> Rectangle {
    return { m_position.x, m_position.y,
             m_frameRec.width * m_scale, m_frameRec.height * m_scale };
}

auto Star::isCollected() const -> bool {
    return m_collected;
}

auto Star::collect() -> void {
    if (!m_collected) {
        m_collected = true;
        s_collectedStars++;
    }
}

auto Star::SpawnRandom(
    const Rectangle &spawnBounds,
    const std::vector<std::unique_ptr<Platform>> &platforms
) -> Star* {
    for (int attempt = 0; attempt < constants::STAR_SPAWN_MAX_ATTEMPTS; attempt++) {
        float x = spawnBounds.x + GetRandomValue(0, static_cast<int>(spawnBounds.width));
        float y = spawnBounds.y + GetRandomValue(0, static_cast<int>(spawnBounds.height));
        Star* potentialStar = new Star({ x, y });
        Rectangle starRect = potentialStar->getBoundingBox();
        bool valid = true;
        for (auto const &platform : platforms) {
            Rectangle platRect = {
                platform->getX(),
                platform->getY(),
                static_cast<float>(platform->getTexture().width) * platform->getScale(),
                static_cast<float>(platform->getTexture().height) * platform->getScale()
            };
            if (CheckCollisionRecs(starRect, platRect)) {
                valid = false;
                break;
            }
        }
        if (valid) {
            return potentialStar;
        }
        delete potentialStar;
    }
    return nullptr;
}

auto Star::getCollectedCount() -> int {
    return s_collectedStars;
}

auto Star::applyDashBoost(float dashBoost) -> void {
    m_position.x -= dashBoost;
}

auto Star::applyMovement(float speed) -> void {
    m_position.x -= speed;
}