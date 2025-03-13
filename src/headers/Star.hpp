#ifndef STAR_HPP
#define STAR_HPP

#include <vector>
#include <memory>
#include <filesystem>
#include "raylib.h"
#include "Platform.h"

class Star {
public:
    // Create a star at a given position.
    Star(Vector2 position);

    ~Star();

    // Update animation. Does nothing if collected.
    void update();

    // Update star movement (shifts the star by speed).
    void applyMovement(float speed);

    // Draw star if not yet collected.
    void draw();

    // Returns the star's bounding box.
    Rectangle getBoundingBox() const;

    // Returns whether this star has been collected.
    bool isCollected() const;

    // Mark as collected and increment global counter.
    void collect();

    // Spawns a star at a random position within spawnBounds
    // ensuring it does not intersect the surface of any platform.
    static Star *SpawnRandom(const Rectangle &spawnBounds,
                             const std::vector<std::unique_ptr<Platform> > &platforms);

    // Returns the total number of stars collected.
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
    float m_animationInterval; // seconds per frame.
    bool m_collected;
    float m_scale; // scale factor
    float m_speed;
    // Added members for spin animation
    float m_rotation; // current rotation angle
    float m_spinSpeed; // degrees per second

    // Global counter for collected stars.
    static int s_collectedStars;
};

#endif // STAR_HPP
