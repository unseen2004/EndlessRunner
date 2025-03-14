#ifndef STAR_HPP
#define STAR_HPP

#include <memory>
#include <vector>
#include "Platform.hpp"
#include "raylib.h"

class Star {
public:
    Star(Vector2 position);

    ~Star();

    auto update() -> void;

    auto changeSpeed(float n) -> void;

    auto draw() -> void;

    auto getBoundingBox() const -> Rectangle;

    auto isCollected() const -> bool;

    auto collect() -> void;

    static auto SpawnRandom(const Rectangle &spawnBounds,
                            const std::vector<std::unique_ptr<Platform>> &platforms) -> Star *;

    static auto getCollectedCount() -> int;

    auto applyDashBoost(float dashBoost) -> void;

private:
    auto applyMovement(float speed) -> void;

    Vector2 m_position;
    Texture2D m_texture;
    Rectangle m_frameRec;
    int m_numFrames;
    int m_currentFrame;
    float m_animationTimer;
    float m_animationInterval;
    bool m_collected;
    float m_scale;
    float m_speed;
    float m_rotation;
    float m_spinSpeed;

    static int s_collectedStars;
};

#endif // STAR_HPP
