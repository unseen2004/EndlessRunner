#ifndef PLATFORM_H
#define PLATFORM_H

#include <filesystem>
#include "raylib.h"
#include "Background.h"
#include "Config.h"
#include "Random.h"

class Platform : public Background {
public:
    Platform(const std::filesystem::path &path, float speed = 0.1f, float x = 0.0f, float y = 70.0f, float scale = 1.0f)
        : Background(path, speed, x, y, scale) {
    }

    void draw();

    bool update();

    bool isOutsite();

    bool touchLeft(const Rectangle &other);

    bool touchRight(const Rectangle &other);

    bool touchDown(const Rectangle &other);

    bool touchUp(const Rectangle &other);

    bool isTouching(const Rectangle &other);


private:
    Rectangle getBounds() const;

protected:
    static std::filesystem::path getRandomPlatformPath();
};

#endif // PLATFORM_H

