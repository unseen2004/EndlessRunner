// Language: cpp
// File: `src/headers/Constants.hpp`

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
    constexpr int STAR_SPAWN_CHANCE_NUMERATOR = 1;
    constexpr int STAR_SPAWN_CHANCE_DENOMINATOR = 100;
    constexpr float STAR_SPAWN_MARGIN = 100.0f;

    // Snow.cpp constants
    constexpr int SNOW_MIN_SPEED = 50;
    constexpr int SNOW_MAX_SPEED = 150;
    constexpr float SNOW_SPEED_DIVISOR = 100.0f;
    constexpr float SNOW_RESET_Y_OFFSET = -3.0f;
    constexpr float SNOW_PARTICLE_RADIUS = 3.0f;
    constexpr float SNOW_PARTICLE_ALPHA = 0.8f;
    constexpr int SNOW_PARTICLE_COUNT = 100;

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

    // ReplayGameScreen.cpp constants
    constexpr int REPLAY_OVERLAY_X = 10;
    constexpr int REPLAY_OVERLAY_Y = 10;
    constexpr int REPLAY_OVERLAY_WIDTH = 120;
    constexpr int REPLAY_OVERLAY_HEIGHT = 30;
    constexpr float REPLAY_OVERLAY_ALPHA = 0.7f;
    constexpr int REPLAY_TEXT_X = 15;
    constexpr int REPLAY_TEXT_Y = 15;
    constexpr int REPLAY_TEXT_SIZE = 20;
    constexpr const char* REPLAY_FINISHED_MESSAGE = "Replay Finished - Press SPACE to return";
    constexpr int REPLAY_FINISHED_TEXT_SIZE = 30;
    constexpr int REPLAY_FINISHED_PADDING = 10;
    constexpr int REPLAY_FINISHED_HEIGHT = 40;
    constexpr float REPLAY_FINISHED_ALPHA = 0.7f;
    constexpr int REPLAY_FINISHED_TEXT_OFFSET = 15;

    // GameScreen.cpp constants
    constexpr float INVULNERABILITY_TIMER = 0.5f;
    constexpr float SPEED_GAME_OVER = 0.0f;
    constexpr float BASE_SPEED = 3.0f;
    constexpr int CLOUD_MIN_Y = 0;
    constexpr int CLOUD_MAX_Y = 100;
    constexpr int CLOUD_MIN_TYPE = 1;
    constexpr int CLOUD_MAX_TYPE = 3;
    constexpr float CLOUD_MIN_SCALE = 1.0f;
    constexpr float CLOUD_MAX_SCALE = 2.0f;
    constexpr float CLOUD_MIN_SPEED_FACTOR = 0.3f;
    constexpr float CLOUD_MAX_SPEED_FACTOR = 0.5f;
    constexpr int BOTTOM_PLATFORM_GAP_MULTIPLIER = 2;
    constexpr int TOP_PLATFORM_GAP_MULTIPLIER = 3;
    constexpr int PLATFORM_BOTTOM_MIN = 700;
    constexpr int PLATFORM_BOTTOM_MAX_OFFSET = 300;
    constexpr int PLATFORM_TOP_MAX = 100;
    constexpr int INITIAL_PLATFORM_X = 300;
    constexpr int INITIAL_PLATFORM_Y = 300;
    constexpr int PLATFORM_GAP = 600;
    constexpr int FONT_BASE_SIZE = 36;
    constexpr const char* DEATH_MESSAGE = "GAME OVER";
    constexpr int DEATH_MSG_OFFSET_X = 100;
    constexpr int DEATH_MSG_OFFSET_Y = 20;
    constexpr int DEATH_MSG_BORDER = 2;
    constexpr int DEATH_MSG_FONT_SIZE = 40;

    // Interface.cpp constants
    constexpr int UI_POSITION_X = 20;
    constexpr int UI_SPEED_Y = 20;
    constexpr int UI_FPS_Y = 50;
    constexpr int UI_STARS_Y = 80;
    constexpr int UI_FONT_SIZE = 20;
    constexpr int CONTROL_HINT_OFFSET = 320;
    constexpr int CONTROL_HINT_Y = 20;
    constexpr int CONTROL_HINT_SPACING = 20;
    constexpr int CONTROL_HINT_SIZE = 16;

    // Platform.cpp constants
    constexpr float PLATFORM_ROTATION = 0.0f;
    constexpr float PLATFORM_SCALE = 1.0f;
    constexpr int MIN_PLATFORM_TYPE = 1;
    constexpr int MAX_PLATFORM_TYPE = 5;
}

#endif // CONSTANTS_HPP