#include "../headers/Game.hpp"
#include "../headers/DebugLog.hpp"

bool g_exitGame = false;

Game::Game() {
    InitWindow(config::SCREEN_WIDTH, config::SCREEN_HEIGHT, "Endless Runner");
    SetTargetFPS(config::FRAMES);
    m_stateMachine.changeState(std::make_unique<WelcomeScreen>(m_stateMachine));
}

Game::~Game() {
    fs::path replayDir = fs::current_path() / "replays";
    LOG("deleting game " << replayDir);
    if (fs::exists(replayDir)) {
        try {
            fs::remove_all(replayDir);
            LOG("Replays directory deleted successfully.");
        } catch (const fs::filesystem_error &e) {
            ERR("Error deleting replays directory: " << e.what());
        }
    }
    CloseWindow();
}

auto Game::run() -> void {
    while (!WindowShouldClose() && !g_exitGame) {
        m_stateMachine.handleInput();
        m_stateMachine.update();
        m_stateMachine.render();
        m_stateMachine.processPendingState();
    }
}