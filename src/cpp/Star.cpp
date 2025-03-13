// Language: cpp
// File: `src/cpp/Star.cpp`
#include "../headers/Star.hpp"
#include "../headers/Platform.h"
#include "raylib.h"
#include <cstdlib>

int Star::s_collectedStars = 0;

Star::Star(Vector2 position)
    : m_position(position), m_numFrames(4), m_currentFrame(0),
      m_animationTimer(0.0f), m_animationInterval(0.1f), m_collected(false), m_scale(0.1f) {
    m_texture = LoadTexture("resources/star.png");
    m_frameRec.x = 0;
    m_frameRec.y = 0;
    m_frameRec.width = m_texture.width / m_numFrames;
    m_frameRec.height = m_texture.height;
}

void Star::update() {
    if(m_collected) return;
    float dt = GetFrameTime();
    m_animationTimer += dt;
    if(m_animationTimer >= m_animationInterval) {
        m_animationTimer = 0.0f;
        m_currentFrame = (m_currentFrame + 1) % m_numFrames;
        m_frameRec.x = m_currentFrame * m_frameRec.width;
    }
}

void Star::draw() {

    DrawTextureEx(m_texture, m_position, 0.0f, m_scale, WHITE);
}
void Star::applyMovement(float speed) {
    // Move the star left by the game speed.
    m_position.x -= speed;
}



Star::~Star() {
    UnloadTexture(m_texture);
}

Rectangle Star::getBoundingBox() const {
    return Rectangle{ m_position.x, m_position.y, m_frameRec.width * m_scale, m_frameRec.height * m_scale };
}

bool Star::isCollected() const {
    return m_collected;
}

void Star::collect() {
    if (!m_collected) {
        m_collected = true;
        s_collectedStars++;
    }
}

int Star::getCollectedCount() {
    return s_collectedStars;
}

Star* Star::SpawnRandom(const Rectangle &spawnBounds,
                        const std::vector<std::unique_ptr<Platform>> &platforms) {
    const int maxAttempts = 50;
    for(int attempt = 0; attempt < maxAttempts; attempt++){
        float x = spawnBounds.x + GetRandomValue(0, static_cast<int>(spawnBounds.width));
        float y = spawnBounds.y + GetRandomValue(0, static_cast<int>(spawnBounds.height));
        Vector2 pos = { x, y };
        Star* potentialStar = new Star(pos);
        Rectangle starRect = potentialStar->getBoundingBox();
        bool valid = true;
        for (const auto &platform : platforms) {
            Rectangle platRect = { platform->getX(), platform->getY(),
                                     static_cast<float>(platform->getTexture().width) * platform->getScale(),
                                     static_cast<float>(platform->getTexture().height) * platform->getScale() };
            if(CheckCollisionRecs(starRect, platRect)){
                valid = false;
                break;
            }
        }
        if(valid){
            return potentialStar;
        }
        delete potentialStar;
    }
    return nullptr;
}