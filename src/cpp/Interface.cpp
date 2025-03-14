// Language: cpp
// File: `src/cpp/Interface.cpp`
#include "../headers/Interface.hpp"
#include "../headers/Config.hpp"

Interface::Interface() {}
Interface::~Interface() {}

void Interface::update() {
    // Optional: add UI logic update if needed.
}

void Interface::draw(float speed, int stars) {
    DrawText(TextFormat("SPEED: %.1f", speed), 20, 20, 20, GREEN);
    DrawText(TextFormat("FPS: %i", (int)(1.0f / GetFrameTime())), 20, 50, 20, GREEN);
    DrawText(TextFormat("Stars: %i", stars), 20, 80, 20, GREEN);
    DrawText("SPACE: Jump (Double Jump Available)", config::SCREEN_WIDTH - 320, 20, 16, GREEN);
    DrawText("SHIFT: Dash", config::SCREEN_WIDTH - 320, 40, 16, GREEN);
}