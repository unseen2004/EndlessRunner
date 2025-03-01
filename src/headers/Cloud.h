#ifndef CLOUD_H
#define CLOUD_H

#include "Background.h"
#include "Random.h"

class Cloud : public Background {
    float m_random_val;
public:

    Cloud(const std::filesystem::path &path, float speed, float random_val, float x, float y, float scale)
        : Background(path, speed, x, y, scale) {
        m_random_val = random_val;
    }



    void draw();

    bool update();
};

#endif // CLOUD_H
