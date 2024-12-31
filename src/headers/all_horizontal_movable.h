#ifndef ALL_HORIZONTAL_MOVABLE_H
#define ALL_HORIZONTAL_MOVABLE_H
#include "includes.h"


class Movable {
protected:
    float m_speed;

public:
    virtual void changeSpeed(float newSpeed) = 0;
    virtual ~Movable() = default;
};

class Background : public Movable {
    float m_x;
    float m_y;
    Texture2D m_texture;

public:
    explicit Background(const char *path, float x = 0.0f, float y = 70.0f, float speed = 0.0f);
    ~Background() override;

    void resetIfOutsite();
    void draw(float x = 0.0f, float y = 70.0f, float rotation = 0.0f, float scale = 2.0f, Color color = WHITE);

    [[nodiscard]] float getX() const;
    void changeX(const float x);
    [[nodiscard]] int getWidth() const;
};

class Platform : public Background {
public:
    Platform(float speed = 0.0f);
    ~Platform() override = default;

private:
    void resetIfOutsite() = delete;

};

class Obstacles : public Movable {
};

#endif // ALL_HORIZONTAL_MOVABLE_H