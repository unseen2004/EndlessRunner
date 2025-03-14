#include "../headers/WelcomeScreen.hpp"
#include "../headers/Config.hpp"
#include "../headers/Constants.hpp"
#include "../headers/DebugLog.hpp"

WelcomeScreen::WelcomeScreen(StateMachine &sm) : stateMachine(sm), m_animationTimer(0.0f) {}

WelcomeScreen::~WelcomeScreen() {}

auto WelcomeScreen::handleInput() -> void {
    if (IsKeyPressed(KEY_ENTER)) {
        stateMachine.changeState(std::make_unique<GameScreen>(stateMachine));
    }
    if (IsKeyPressed(KEY_R)) {
        stateMachine.changeState(std::make_unique<ReplayScreen>(stateMachine));
    }
    if (IsKeyPressed(KEY_F)) {
        config::fog = !config::fog;
    }
    if (IsKeyPressed(KEY_S)) {
        config::snow = !config::snow;
    }
}

auto WelcomeScreen::update() -> void { m_animationTimer += GetFrameTime(); }

auto WelcomeScreen::render() -> void {
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));
    const char *message = "Press Enter to Start Game, R to Replay";
    Vector2 startPos{constants::START_POS_X, constants::START_POS_Y};
    for (int i = 0; message[i] != '\0'; i++) {
        float yOffset = sinf(m_animationTimer * constants::ANIMATION_MULTIPLIER + i) * constants::Y_OFFSET_AMPLITUDE;
        char tempStr[2] = {message[i], '\0'};
        DrawTextEx(GetFontDefault(), tempStr, {startPos.x + i * constants::LETTER_SPACING, startPos.y + yOffset}, 20, 1,
                   WHITE);
    }
    const char *fogStatus = config::fog ? "Fog is on - press f to change" : "Fog is off - press f to change";
    const char *snowStatus = config::snow ? "Snow is on - press s to change" : "Snow is off - press s to change";
    DrawTextEx(GetFontDefault(), fogStatus, {startPos.x, startPos.y + constants::OFFSET_FOG}, 20, 1, YELLOW);
    DrawTextEx(GetFontDefault(), snowStatus, {startPos.x, startPos.y + constants::OFFSET_SNOW}, 20, 1, YELLOW);
    EndDrawing();
}
