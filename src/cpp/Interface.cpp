#include "../headers/Interface.hpp"
#include "../headers/Config.hpp"
#include "../headers/Constants.hpp"
#include "../headers/DebugLog.hpp"

Interface::Interface() {
    LOG("Interface initialized");
}

Interface::~Interface() {
    LOG("Interface destroyed");
}

void Interface::update() {
    // Optional: add UI logic update if needed.
    LOG("Interface updated");
}

void Interface::draw(float speed, int stars) {
    // Draw speed information
    DrawText(
        TextFormat("SPEED: %.1f", speed),
        constants::UI_POSITION_X,
        constants::UI_SPEED_Y,
        constants::UI_FONT_SIZE,
        GREEN
    );

    // Draw FPS information
    DrawText(
        TextFormat("FPS: %i", (int)(1.0f / GetFrameTime())),
        constants::UI_POSITION_X,
        constants::UI_FPS_Y,
        constants::UI_FONT_SIZE,
        GREEN
    );

    // Draw star count
    DrawText(
        TextFormat("Stars: %i", stars),
        constants::UI_POSITION_X,
        constants::UI_STARS_Y,
        constants::UI_FONT_SIZE,
        GREEN
    );

    // Draw control hints
    DrawText(
        "SPACE: Jump (Double Jump Available)",
        config::SCREEN_WIDTH - constants::CONTROL_HINT_OFFSET,
        constants::CONTROL_HINT_Y,
        constants::CONTROL_HINT_SIZE,
        GREEN
    );

    DrawText(
        "SHIFT: Dash",
        config::SCREEN_WIDTH - constants::CONTROL_HINT_OFFSET,
        constants::CONTROL_HINT_Y + constants::CONTROL_HINT_SPACING,
        constants::CONTROL_HINT_SIZE,
        GREEN
    );
}