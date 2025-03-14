#include "../headers/Star.hpp"
#include "../headers/Constants.hpp"
#include "../headers/DebugLog.hpp"

int Star::s_collectedStars = 0;

Star::Star(Vector2 position)
    : m_position(position), m_numFrames(constants::STAR_FRAMES), m_currentFrame(0),
      m_animationTimer(0.0f), m_animationInterval(constants::STAR_ANIMATION_INTERVAL),
      m_collected(false), m_scale(constants::STAR_SCALE) {
    m_texture = LoadTexture("resources/star.png");
    m_frameRec.x = 0;
    m_frameRec.y = 0;
    m_frameRec.width = m_texture.width / m_numFrames;
    m_frameRec.height = m_texture.height;
    LOG("Star created at position (" << position.x << ", " << position.y << ")");
}

void Star::update() {
    applyMovement(m_speed);
    LOG("Star speed: " << m_speed << ", position: " << m_position.x);
}

void Star::changeSpeed(float n) {
    m_speed = n;
    LOG("Star speed changed to " << n);
}

void Star::draw() {
    DrawTextureEx(m_texture, m_position, constants::STAR_ROTATION, m_scale, WHITE);
}

void Star::applyMovement(float speed) {
    // Move the star left by the game speed.
    m_position.x -= speed;
}

Star::~Star() {
    UnloadTexture(m_texture);
    LOG("Star destroyed");
}

Rectangle Star::getBoundingBox() const {
    return Rectangle{ m_position.x, m_position.y,
                     m_frameRec.width * m_scale, m_frameRec.height * m_scale };
}

void Star::applyDashBoost(float dashBoost) {
    m_position.x -= dashBoost;
}

bool Star::isCollected() const {
    return m_collected;
}

void Star::collect() {
    if (!m_collected) {
        m_collected = true;
        s_collectedStars++;
        LOG("Star collected. Total stars: " << s_collectedStars);
    }
}

int Star::getCollectedCount() {
    return s_collectedStars;
}

Star* Star::SpawnRandom(const Rectangle &spawnBounds,
                      const std::vector<std::unique_ptr<Platform>> &platforms) {
    const int maxAttempts = constants::STAR_SPAWN_MAX_ATTEMPTS;
    for(int attempt = 0; attempt < maxAttempts; attempt++) {
        float x = spawnBounds.x + GetRandomValue(0, static_cast<int>(spawnBounds.width));
        float y = spawnBounds.y + GetRandomValue(0, static_cast<int>(spawnBounds.height));
        Vector2 pos = { x, y };
        Star* potentialStar = new Star(pos);
        Rectangle starRect = potentialStar->getBoundingBox();
        bool valid = true;
        for (const auto &platform : platforms) {
            Rectangle platRect = {
                platform->getX(),
                platform->getY(),
                static_cast<float>(platform->getTexture().width) * platform->getScale(),
                static_cast<float>(platform->getTexture().height) * platform->getScale()
            };
            if(CheckCollisionRecs(starRect, platRect)) {
                valid = false;
                break;
            }
        }
        if(valid) {
            LOG("Successfully spawned star at attempt " << attempt);
            return potentialStar;
        }
        delete potentialStar;
    }
    LOG("Failed to spawn star after " << maxAttempts << " attempts");
    return nullptr;
}