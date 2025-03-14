#include "../headers/DeadScreen.hpp"
#include "../headers/DebugLog.hpp"
#include "../headers/Constants.hpp"

extern bool g_exitGame;
DeadScreen::DeadScreen(StateMachine &sm) : stateMachine(sm) {}
DeadScreen::~DeadScreen() {}

void DeadScreen::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        stateMachine.changeState(std::make_unique<WelcomeScreen>(stateMachine));
    }
    if (IsKeyPressed(KEY_E)) {
        g_exitGame = true;
    }
}

void DeadScreen::update() {
    // Dead screen update logic
}

void DeadScreen::render() {
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));
    DrawText("Dead Screen - Press Enter to Continue, E to Exit",
             constants::DEAD_SCREEN_X, constants::DEAD_SCREEN_Y,
             constants::DEAD_SCREEN_FONT_SIZE, BLACK);
    EndDrawing();
}