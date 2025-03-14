#include "../headers/Game.h"
bool g_exitGame = false;
Game::Game() {
    InitWindow(config::SCREEN_WIDTH, config::SCREEN_HEIGHT, "Endless Runner");
    SetTargetFPS(config::FRAMES);

    m_stateMachine.changeState(std::make_unique<WelcomeScreen>(m_stateMachine));

}


Game::~Game() {
        fs::path replayDir = fs::current_path() / "replays";
        std::cout<<"deleting game "<<replayDir<<std::endl;
    if (fs::exists(replayDir)) {
        try {
            fs::remove_all(replayDir);
            std::cout << "Replays directory deleted successfully." << std::endl;
        } catch (const fs::filesystem_error &e) {
            std::cerr << "Error deleting replays directory: " << e.what() << std::endl;
        }
    }
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose() && !g_exitGame) {
        // Handle input
        m_stateMachine.handleInput();

        // Update game state
        m_stateMachine.update();

        // Render game state
        m_stateMachine.render();
        m_stateMachine.processPendingState();

    }
}
