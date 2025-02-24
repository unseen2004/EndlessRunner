#ifndef CLOUD_H
#define CLOUD_H

#include "Background.h"

class Cloud : public Background {
public:

    Cloud(const std::filesystem::path &path, float speed, float x, float y, float scale)
        : Background(path, speed, x, y, scale) {
    }

    ~Cloud();

    void draw();

    bool update();
};

#endif // CLOUD_H
