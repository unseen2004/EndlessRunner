#ifndef CONFIG_H
#define CONFIG_H

namespace config {
    constexpr int SCREEN_WIDTH = 1920;
    constexpr int SCREEN_HEIGHT = 1080;
    constexpr int FRAMES = 60;
    constexpr int MAX_CHARACTER_FRAME_SPEED = 15;
    constexpr int MIN_CHARACTER_FRAME_SPEED = 1;
    constexpr int JUMPS_NUMBER = 2;
    constexpr int MAX_CLOUDS = 3;
    constexpr int MAX_PLATFORMS = 2;
    constexpr float GRAVITY = 0.5; // use
    constexpr float JUMP_FORCE = 10; // use
    constexpr float DASH_FORCE = 10; // use
    constexpr float DASH_COOLDOWN = 0.5; // use
    constexpr int PLATFORM_TIME_COOLDOWN = 60;
    constexpr int PLATFORM_WIDTH = 500;
    constexpr float e = 0.1;
}


#endif // CONFIG_H

