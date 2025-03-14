// Language: cpp
// File: `src/cpp/WelcomeScreen.cpp`
#include "../headers/WelcomeScreen.hpp"
#include "../headers/Config.hpp"
#include "../headers/Constants.hpp"
#include "../headers/DebugLog.hpp"

WelcomeScreen::WelcomeScreen(StateMachine &sm) : stateMachine(sm), m_animationTimer(0.0f) {
    LOG("WelcomeScreen initialized");
}

WelcomeScreen::~WelcomeScreen() {
    LOG("WelcomeScreen destroyed");
}

void WelcomeScreen::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        LOG("User pressed ENTER - changing to GameScreen");
        stateMachine.changeState(std::make_unique<GameScreen>(stateMachine));
    }
    if(IsKeyPressed(KEY_R)) {
        LOG("User pressed R - changing to ReplayScreen");
        stateMachine.changeState(std::make_unique<ReplayScreen>(stateMachine));
    }
    if(IsKeyPressed(KEY_F)) {
        config::fog = !config::fog;
        LOG("Fog setting changed to: " << (config::fog ? "ON" : "OFF"));
    }
    if(IsKeyPressed(KEY_S)) {
        config::snow = !config::snow;
        LOG("Snow setting changed to: " << (config::snow ? "ON" : "OFF"));
    }
}

void WelcomeScreen::update() {
    // Update the animation timer.
    m_animationTimer += GetFrameTime();
}

void WelcomeScreen::render() {
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));

    // Define the text and its starting position.
    const char *message = "Press Enter to Start Game, R to Replay";
    Vector2 startPos { constants::START_POS_X, constants::START_POS_Y };

    // Draw the animated pixel style text letter by letter.
    for (int i = 0; message[i] != '\0'; i++) {
        float yOffset = sinf(m_animationTimer * constants::ANIMATION_MULTIPLIER + i) * constants::Y_OFFSET_AMPLITUDE;
        char tempStr[2] = { message[i], '\0' };
        DrawTextEx(GetFontDefault(), tempStr,
                   (Vector2){ startPos.x + i * constants::LETTER_SPACING, startPos.y + yOffset },
                   20, 1, WHITE);
    }

    // Use the inline config variables for fog and snow.
    const char *fogStatus = config::fog ? "Fog is on - press f to change" : "Fog is off - press f to change";
    const char *snowStatus = config::snow ? "Snow is on - press s to change" : "Snow is off - press s to change";
    const char *info = "In game press space to jump and left shift to dash";

    // Draw status text below the main message.
    DrawTextEx(GetFontDefault(), fogStatus, (Vector2){ startPos.x, startPos.y + constants::OFFSET_FOG }, 20, 1, YELLOW);
    DrawTextEx(GetFontDefault(), snowStatus, (Vector2){ startPos.x, startPos.y + constants::OFFSET_SNOW }, 20, 1, YELLOW);
    DrawTextEx(GetFontDefault(), info, (Vector2){ startPos.x, startPos.y + constants::OFFSET_INFO }, 20, 1, YELLOW);

    EndDrawing();
}