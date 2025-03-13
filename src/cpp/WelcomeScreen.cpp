// Language: cpp
// File: `src/cpp/WelcomeScreen.cpp`
#include "../headers/WelcomeScreen.h"
#include "../headers/Config.h"

WelcomeScreen::WelcomeScreen(StateMachine &sm) : stateMachine(sm), m_animationTimer(0.0f) {}

WelcomeScreen::~WelcomeScreen() {}

void WelcomeScreen::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        stateMachine.changeState(std::make_unique<GameScreen>(stateMachine));
    }
    if(IsKeyPressed(KEY_F)) {
        config::fog = !config::fog;
    }
    if(IsKeyPressed(KEY_S)) {
        config::snow = !config::snow;
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
    const char *message = "Press Enter to Start Game";
    Vector2 startPos = { 200, 200 };

    // Draw the animated pixel style text letter by letter.
    float letterSpacing = 20.0f;
    for (int i = 0; message[i] != '\0'; i++) {
        float yOffset = sinf(m_animationTimer * 5.0f + i) * 2.0f;
        char tempStr[2] = { message[i], '\0' };
        DrawTextEx(GetFontDefault(), tempStr,
                   (Vector2){ startPos.x + i * letterSpacing, startPos.y + yOffset },
                   20, 1, WHITE);
    }

    // Use the inline config variables for fog and snow.
    const char *fogStatus = config::fog ? "Fog is on - press f to change" : "Fog is off - press f to change";
    const char *snowStatus = config::snow ? "Snow is on - press s to change" : "Snow is off - press s to change";

    // Draw status text below the main message.
    DrawTextEx(GetFontDefault(), fogStatus, (Vector2){ startPos.x, startPos.y + 40 }, 20, 1, YELLOW);
    DrawTextEx(GetFontDefault(), snowStatus, (Vector2){ startPos.x, startPos.y + 70 }, 20, 1, YELLOW);

    EndDrawing();
}