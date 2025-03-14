#include "../headers/ReplayScreen.hpp"
#include "../headers/Constants.hpp"
#include "../headers/DebugLog.hpp"
#include "../headers/ReplayGameScreen.hpp"
#include "../headers/WelcomeScreen.hpp"

namespace fs = std::filesystem;

ReplayScreen::ReplayScreen(StateMachine &sm) : m_stateMachine(sm), m_selectedIndex(0), m_inReplay(false) {
    LOG("ReplayScreen initialized");
    loadSavedGames();
}

ReplayScreen::~ReplayScreen() { LOG("ReplayScreen destroyed"); }

auto ReplayScreen::loadSavedGames() -> void {
    m_savedGames.clear();
    fs::path replayDir = fs::current_path() / "replays";
    if (fs::exists(replayDir)) {
        for (const auto &entry: fs::directory_iterator(replayDir)) {
            if (entry.path().extension() == ".dat") {
                auto filename = entry.path().filename().string();
                m_savedGames.push_back({filename, filename});
            }
        }
    }
    if (m_savedGames.empty()) {
        m_savedGames.push_back({"", constants::NO_SAVED_GAMES_TEXT});
    }
    m_selectedIndex = 0;
    LOG("Loaded " << m_savedGames.size() << " saved replays");
}

auto ReplayScreen::startReplay(const std::string &filename) -> void {
    LOG("Starting replay: " << filename);
    m_stateMachine.changeState(std::make_unique<ReplayGameScreen>(m_stateMachine, filename));
}

auto ReplayScreen::handleInput() -> void {
    if (!m_inReplay) {
        if (IsKeyPressed(KEY_UP)) {
            m_selectedIndex = (m_selectedIndex > 0) ? m_selectedIndex - 1 : static_cast<int>(m_savedGames.size()) - 1;
        }
        if (IsKeyPressed(KEY_DOWN)) {
            m_selectedIndex = (m_selectedIndex + 1) % m_savedGames.size();
        }
        if (IsKeyPressed(KEY_ENTER)) {
            if (!m_savedGames[m_selectedIndex].first.empty()) {
                startReplay(m_savedGames[m_selectedIndex].first);
            }
        }
        if (IsKeyPressed(KEY_F)) {
            LOG("Returning to welcome screen");
            m_stateMachine.changeState(std::make_unique<WelcomeScreen>(m_stateMachine));
        }
    }
}

auto ReplayScreen::update() -> void { handleInput(); }

auto ReplayScreen::render() -> void {
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));
    DrawTextEx(GetFontDefault(), constants::REPLAY_SCREEN_TITLE, {constants::REPLAY_TITLE_X, constants::REPLAY_TITLE_Y},
               constants::REPLAY_TITLE_SIZE, constants::REPLAY_TEXT_SPACING, WHITE);
    float startY = constants::REPLAY_LIST_START_Y;
    for (size_t i = 0; i < m_savedGames.size(); i++) {
        auto color = (i == m_selectedIndex) ? RED : WHITE;
        DrawText(m_savedGames[i].second.c_str(), constants::REPLAY_LIST_X, startY + i * constants::REPLAY_ITEM_HEIGHT,
                 constants::REPLAY_ITEM_FONT_SIZE, color);
    }
    EndDrawing();
}
