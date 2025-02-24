#include "../headers/GameScreen.h"

GameScreen::GameScreen(StateMachine& sm) : stateMachine(sm) {}
GameScreen::~GameScreen() {}

void GameScreen::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        stateMachine.changeState(std::make_unique<DeadScreen>(stateMachine)); // Change to DeadScreen
    }
}

void GameScreen::update() {
    // Game update logic
}

void GameScreen::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Game Screen - Press Enter to Die", 200, 200, 20, BLACK);
    EndDrawing();
}