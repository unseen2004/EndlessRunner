// Language: cpp
// File: `src/headers/Interface.h`
#ifndef INTERFACE_H
#define INTERFACE_H

#include "raylib.h"

class Interface {
public:
    Interface();

    ~Interface();

    void update();

    // Draw UI texts using the game speed and stars count.
    void draw(float speed, int stars);
};

#endif // INTERFACE_H
