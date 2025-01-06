#ifndef ALL_HORIZONTAL_MOVABLE_H
#define ALL_HORIZONTAL_MOVABLE_H

#include "includes.h"
#include <filesystem>

class Background {
protected:
    float m_x;
    float m_y;
    float m_speed;
    float m_scale;
    Texture2D m_texture;
    std::filesystem::path m_texturePath;

public:
    explicit Background(const std::filesystem::path& path, float speed = 0.1f,float x = 0.0f, float y = 0.0f, float m_scale = 2.0f);
    ~Background();

    void resetIfOutsite();
    void draw(float x = 0.0f, float y = 0.0f, float rotation = 0.0f, float scale = 2.0f, Color color = WHITE);
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    void changeSpeed(const float speed);
    [[nodiscard]] int getWidth() const;
    void update();
};
class Cloud : public Background {
public:
    Cloud(const std::filesystem::path& path, float speed , float x , float y, float scale )
        : Background(path, speed, x, y, scale) {}
    ~Cloud() = default;
    void draw();
    bool update();
};
class Platform : public Background {
public:
    Platform(const std::filesystem::path& path, float speed = 0.1f, float x = 0.0f, float y = 70.0f, float m_scale = 1.0f)
        : Background(path, speed, x, y) {}
    ~Platform() = default;

    bool resetIfOutsite() ; // to do
    void draw();
    bool update(); // to do
    bool isOutsite(); // to do

    bool touchLeft(const Rectangle& other);
    bool touchRight(const Rectangle& other);
    bool touchDown(const Rectangle& other);
    bool touchUp(const Rectangle& other);
    bool isTouching(const Rectangle& other);

private:
    Rectangle getBounds() const;
protected:
    static std::filesystem::path getRandomPlatformPath();
};

class Obstacles : public Platform {
public:
    Obstacles();
    ~Obstacles();

    bool update();
    void draw();

private:
    Texture2D m_obstacle_texture;
    Vector2 m_obstacle_position;
    static std::filesystem::path getRandomObstaclePath();
};

#endif // ALL_HORIZONTAL_MOVABLE_H