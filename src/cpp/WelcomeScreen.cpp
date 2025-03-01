#include "../headers/WelcomeScreen.h"

WelcomeScreen::WelcomeScreen(StateMachine& sm) : stateMachine(sm) {}
WelcomeScreen::~WelcomeScreen() {}

void WelcomeScreen::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        stateMachine.changeState(std::make_unique<GameScreen>(stateMachine)); // Change to the next state
    }
}

void WelcomeScreen::update() {
    // No update logic needed for this simple screen
}

void WelcomeScreen::render() {

          BeginDrawing();
        ClearBackground(GetColor(0x052c46ff));
  DrawText("Press Enter to Start Game", 200, 200, 20, BLACK);

        EndDrawing();
}