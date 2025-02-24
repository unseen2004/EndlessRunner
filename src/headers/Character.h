#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <filesystem>
#include "raylib.h"
#include "Config.h"

namespace character_const {
    constexpr int NUM_FRAMES_PER_LINE = 5;
    constexpr int NUM_LINES = 5;
};

class Character {
    Vector2 m_position;
    int m_currentFrame;
    int m_framesCounter;
    int m_framesSpeed;
    int m_jumps_left;
    bool m_is_jumping;
    int m_currentLine;
    Texture2D m_character;
    Texture2D m_explosion;
    Sound m_boom;
    std::filesystem::path m_path_character;
    std::filesystem::path m_path_explosion;
    std::filesystem::path m_path_sound;
    Rectangle m_frame_rec;

public:
    Character(std::filesystem::path path1, std::filesystem::path path2, std::filesystem::path path3, float x = 300,
              float y = 800, int currentFrame = 0, int framesCounter = 0,
              int framesSpeed = 8, int currentLine = 0, bool is_jumping = false);

    ~Character();

    void run();

    void die();

    bool init_jump();

    void jump();

    void dash();

    void draw();

    bool checkCollision();

    void changeSpeed(int n);

    void newSpeed(int n);
};

#endif // CHARACTER_H

