#include "../headers/Game.h"

Game::Game() {
    InitWindow(config::SCREEN_WIDTH, config::SCREEN_HEIGHT, "Endless Runner");
    SetTargetFPS(config::FRAMES);

	StateMachine stateMachine;
    m_stateMachine.changeState(std::make_unique<WelcomeScreen>(m_stateMachine));

}


Game::~Game() {
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose()) {
        // Handle input
        m_stateMachine.handleInput();

        // Update game state
        m_stateMachine.update();

        // Render game state
        BeginDrawing();
        ClearBackground(RAYWHITE);
        m_stateMachine.render();
        EndDrawing();
    }
}
