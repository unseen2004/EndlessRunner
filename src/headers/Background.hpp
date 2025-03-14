#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <filesystem>
#include <iostream>
#include "raylib.h"

class Background {
protected:
    float m_x;
    float m_y;
    float m_speed;
    float m_scale;
    Texture2D m_texture;
    std::filesystem::path m_texturePath;

public:
    explicit Background(const std::filesystem::path &path, float speed = 0.1F, float x = 0.0f, float y = 0.0f,
                        float m_scale = 2.0f);

    ~Background();

    void resetIfOutsite();

    void draw(float x = 0.0f, float y = 0.0f, float rotation = 0.0f, float scale = 2.0f, Color color = WHITE);

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    void changeSpeed(float speed);

    [[nodiscard]] int getWidth() const;

    void update();

    void applyDashBoost(float dashBoost) {
        std::cout << "Applying dash boost to background" << std::endl;
        m_x -= dashBoost;
    }
};

#endif // BACKGROUND_HPP
