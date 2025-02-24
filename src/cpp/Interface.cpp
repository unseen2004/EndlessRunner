#include "../headers/Interface.h"

Interface::Interface() {}
Interface::~Interface() {}

void Interface::update() {
    // Update UI logic
}

void Interface::draw() {
    // Draw UI on screen; for example, display a placeholder score.
    DrawText("Score: 0", 10, 10, 20, BLACK);
}