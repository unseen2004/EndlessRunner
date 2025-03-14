// File: src/cpp/ReplayScreen.cpp
#include "../headers/ReplayScreen.h"
#include "../headers/WelcomeScreen.h"
#include "../headers/ReplayGameScreen.h"
#include "raylib.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

ReplayScreen::ReplayScreen(StateMachine &sm)
    : m_stateMachine(sm), m_selectedIndex(0), m_inReplay(false)
{
    loadSavedGames();
}

ReplayScreen::~ReplayScreen() {
    std::cout << "Destructing ReplayScreen" << std::endl;
}

// File: src/cpp/ReplayScreen.cpp
// Language: cpp
void ReplayScreen::loadSavedGames() {
    m_savedGames.clear();
    fs::path replayDir = fs::current_path() / "replays";
    if (fs::exists(replayDir)) {
        for (const auto &entry : fs::directory_iterator(replayDir)) {
            if (entry.path().extension() == ".dat") {
                std::string filename = entry.path().filename().string();
                m_savedGames.push_back({filename, filename});
            }
        }
    }
    if (m_savedGames.empty()) {
        m_savedGames.push_back({"", "No saved games found"});
    }
    m_selectedIndex = 0;
}

void ReplayScreen::startReplay(const std::string &filename) {
    // Change state to a new ReplayGameScreen passing the selected replay file.
    std::cout<<"in start replay"<<std::endl;
    m_stateMachine.changeState(std::make_unique<ReplayGameScreen>(m_stateMachine, filename));
}

void ReplayScreen::handleInput() {
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
            m_stateMachine.changeState(std::make_unique<WelcomeScreen>(m_stateMachine));
        }
    }
}

void ReplayScreen::update() {
    handleInput();
}

void ReplayScreen::render() {
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));
    DrawTextEx(GetFontDefault(), "Select a Saved Game: (Enter to replay, F to go back)",
               {50, 50}, 20, 1, WHITE);
    float startY = 100.0f;
    for (size_t i = 0; i < m_savedGames.size(); i++) {
        Color color = (i == m_selectedIndex) ? RED : WHITE;
        DrawText(m_savedGames[i].second.c_str(), 50, startY + i * 30, 20, color);
    }
    EndDrawing();
}