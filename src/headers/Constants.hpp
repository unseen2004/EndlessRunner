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

    // StarPopout.cpp constants
    constexpr float STAR_POPOUT_DURATION = 3.0f;
    constexpr float STAR_POPOUT_SPACING = 2.0f;

    // Star.cpp constants
    constexpr int STAR_FRAMES = 4;
    constexpr float STAR_ANIMATION_INTERVAL = 0.1f;
    constexpr float STAR_SCALE = 0.1f;
    constexpr float STAR_ROTATION = 0.0f;
    constexpr int STAR_SPAWN_MAX_ATTEMPTS = 50;

    // Snow.cpp constants
    constexpr int SNOW_MIN_SPEED = 50;
    constexpr int SNOW_MAX_SPEED = 150;
    constexpr float SNOW_SPEED_DIVISOR = 100.0f;
    constexpr float SNOW_RESET_Y_OFFSET = -3.0f;
    constexpr float SNOW_PARTICLE_RADIUS = 3.0f;
    constexpr float SNOW_PARTICLE_ALPHA = 0.8f;
    // ReplaySystem.cpp constants
    constexpr int RANDOM_SEED_MAX = 100000;
    constexpr int TIMESTAMP_BUFFER_SIZE = 80;
    constexpr const char* DEFAULT_REPLAY_FILENAME = "history.dat";

    // ReplayScreen.cpp constants
    constexpr const char* NO_SAVED_GAMES_TEXT = "No saved games found";
    constexpr const char* REPLAY_SCREEN_TITLE = "Select a Saved Game: (Enter to replay, F to go back)";
    constexpr float REPLAY_TITLE_X = 50.0f;
    constexpr float REPLAY_TITLE_Y = 50.0f;
    constexpr float REPLAY_TITLE_SIZE = 20.0f;
    constexpr float REPLAY_TEXT_SPACING = 1.0f;
    constexpr float REPLAY_LIST_START_Y = 100.0f;
    constexpr float REPLAY_LIST_X = 50.0f;
    constexpr float REPLAY_ITEM_HEIGHT = 30.0f;
    constexpr int REPLAY_ITEM_FONT_SIZE = 20;
}

#endif // CONSTANTS_HPP