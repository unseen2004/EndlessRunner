#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include <filesystem>

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
    std::filesystem::path m_pathCharacter;
    std::filesystem::path m_pathExplosion;
    std::filesystem::path m_pathSound;
    Rectangle m_frameRec;

public:
    Character(std::filesystem::path path1, std::filesystem::path path2, std::filesystem::path path3, float x = 300,
              float y = 800, int currentFrame = 0, int framesCounter = 0,
              int framesSpeed = 8, int currentLine = 0, bool is_jumping = false);
    ~Character();

    void run();
    void dead();
    bool init_jump();
    void jump();
    void dash();
    void changeSpeed(int n);
    void newSpeed(int n);
};

#endif // CHARACTER_H