#include "../headers/DeadScreen.h"

DeadScreen::DeadScreen(StateMachine& sm) : stateMachine(sm) {}
DeadScreen::~DeadScreen() {}

void DeadScreen::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        stateMachine.changeState(std::make_unique<WelcomeScreen>(stateMachine)); // Change to WelcomeScreen
    }
}

void DeadScreen::update() {
    // Dead screen update logic
}

void DeadScreen::render() {
    DrawText("Dead Screen - Press Enter to Restart", 200, 200, 20, BLACK);
}