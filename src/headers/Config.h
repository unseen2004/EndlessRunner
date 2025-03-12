#pragma once

namespace config {
    constexpr int SCREEN_WIDTH = 1920;
    constexpr int SCREEN_HEIGHT = 1080;
    constexpr int FRAMES = 60;
    constexpr float CHARACTER_START_X = 200.0f;
    constexpr float CHARACTER_START_Y = 500.0f;
    constexpr int MAX_PLATFORMS = 2;
    constexpr int MAX_CLOUDS = 5;
    constexpr float PLATFORM_WIDTH = 300.0f;
    constexpr int JUMPS_NUMBER = 2;
    constexpr float BASE_GRAVITY = 0.4f;
    constexpr float BASE_JUMP_FORCE = -15.0f;
    constexpr int BASE_CHARACTER_FRAME_SPEED = 8;
    constexpr float e = 0.05f;
    constexpr bool DEBUG_COLLISION = false;
}
