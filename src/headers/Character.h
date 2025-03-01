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
    float m_speed{1};
    bool m_input_jump{};
    bool m_input_dash{};
    bool m_is_alive{true};
    int m_prev_jump{};


public:
    Character(std::filesystem::path path1, std::filesystem::path path2, std::filesystem::path path3,float m_speed = 0.1f ,float x = 300,
              float y = 800, int currentFrame = 0, int framesCounter = 0,
              int framesSpeed = 8, int currentLine = 0, bool is_jumping = false);

    ~Character();
private:
    void run();

    void die();

    void go_up();

    void go_down();

    void dash();

    bool checkCollision();
public:
    bool update(bool input_jump, bool input_dash);

    void draw();

    void changeSpeed(int n);

    void newSpeed(int n);

    void resetJump();
};

#endif // CHARACTER_H

