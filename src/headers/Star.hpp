#ifndef STAR_HPP
#define STAR_HPP

#include <vector>
#include <memory>
#include <filesystem>
#include <cstdlib>
#include <iostream>
#include "raylib.h"
#include "Platform.hpp"

class Star {
public:
    Star(Vector2 position);

    ~Star();

    void update();

    void applyMovement(float speed);

    void draw();

    Rectangle getBoundingBox() const;

    bool isCollected() const;

    void collect();

    static Star *SpawnRandom(const Rectangle &spawnBounds, const std::vector<std::unique_ptr<Platform> > &platforms);

    static int getCollectedCount();

    void changeSpeed(float n);

    void applyDashBoost(float dashBoost);

private:
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
