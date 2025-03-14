#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "raylib.h"

class Interface {
public:
    Interface();

    ~Interface();

    auto update() -> void;

    auto draw(float speed, int stars) -> void;
};

#endif // INTERFACE_HPP
