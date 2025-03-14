#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace constants {
    // DeadScreen.cpp
    constexpr int DEAD_SCREEN_X = 200;
    constexpr int DEAD_SCREEN_Y = 200;
    constexpr int DEAD_SCREEN_FONT_SIZE = 20;

    // Background.cpp
    constexpr int BACKGROUND_WIDTH_MULTIPLIER = 2;

    // WelcomeScreen.cpp
    constexpr float ANIMATION_MULTIPLIER = 5.0f;
    constexpr float Y_OFFSET_AMPLITUDE = 2.0f;
    constexpr float LETTER_SPACING = 20.0f;
    constexpr int START_POS_X = 200;
    constexpr int START_POS_Y = 200;
    constexpr int OFFSET_FOG = 40;
    constexpr int OFFSET_SNOW = 70;
    constexpr int OFFSET_INFO = 100;

    // Character.cpp
    constexpr int MAX_CHARACTER_FRAME = 5;
    constexpr float CHARACTER_FRAME_DIVISOR = 6.0f;
    constexpr float MAX_VERTICAL_VELOCITY = 15.0f;
    // Explosion animation
    constexpr int EXPLOSION_FPS = 2;
    constexpr int EXPLOSION_MAX_FRAME = 5;
    constexpr int EXPLOSION_MAX_LINE = 5;
    // Collision and grounded checks
    constexpr float GROUND_SCAN_RANGE = 10.0f;
    constexpr float GROUND_STEP = 1.0f;
    constexpr int NUM_SAMPLES = 5;
    constexpr float HEAD_REGION_DIVISOR = 5.0f;
    constexpr int COLLISION_THRESHOLD = 1;
    constexpr float TOP_SAMPLE_OFFSET = -1.0f;
}

#endif // CONSTANTS_HPP