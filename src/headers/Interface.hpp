#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "raylib.h"

class Interface {
public:
    Interface();

    ~Interface();

    void update();

    void draw(float speed, int stars);
};

#endif // INTERFACE_HPP
