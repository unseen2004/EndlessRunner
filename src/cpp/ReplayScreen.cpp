// Language: cpp
// File: src/cpp/ReplayScreen.cpp
#include "../headers/ReplayScreen.h"
#include "../headers/WelcomeScreen.h"
#include "../headers/GameScreen.h"
#include "raylib.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

ReplayScreen::ReplayScreen(StateMachine &sm)
    : m_stateMachine(sm), m_replaySystem(nullptr), m_inReplay(false)
{
    // Load list of saved replay files from the current directory (or a designated folder)
    loadSavedGames();
}

ReplayScreen::~ReplayScreen() {
    std::cout << "Destructing ReplayScreen" << std::endl;
}

void ReplayScreen::loadSavedGames() {
    m_savedGames.clear();
    // For example, list all .dat files in the current directory
    for (const auto &entry : fs::directory_iterator(fs::current_path())) {
        if (entry.path().extension() == ".dat") {
            m_savedGames.push_back(entry.path().filename().string());
        }
    }
    if (m_savedGames.empty()) {
        m_savedGames.push_back("No saved games found");
    }
    m_selectedIndex = 0;
}

void ReplayScreen::startReplay(const std::string &filename) {
    // Create a new ReplaySystem instance, load the chosen replay file, and start playback.
    m_replaySystem = std::make_unique<ReplaySystem>();
    if (m_replaySystem->loadFromFile(filename)) {
        m_replaySystem->startPlayback();
        m_inReplay = true;
    } else {
        std::cerr << "Failed to load replay: " << filename << std::endl;
    }
}

void ReplayScreen::handleInput() {
    if (!m_inReplay) {
        // In List mode: Use Up/Down to change selection and Enter to select a replay.
        if (IsKeyPressed(KEY_UP)) {
            m_selectedIndex = (m_selectedIndex - 1 + m_savedGames.size()) % m_savedGames.size();
        }
        if (IsKeyPressed(KEY_DOWN)) {
            m_selectedIndex = (m_selectedIndex + 1) % m_savedGames.size();
        }
        if (IsKeyPressed(KEY_ENTER)) {
            // Start replay if valid file exists.
            if (!m_savedGames.empty() && m_savedGames[0] != "No saved games found") {
                startReplay(m_savedGames[m_selectedIndex]);
            }
        }
        // Press F to return to welcome screen.
        if (IsKeyPressed(KEY_F)) {
            m_stateMachine.changeState(std::make_unique<WelcomeScreen>(m_stateMachine));
        }
    }
    else {
        // In replay mode. Optionally allow pressing F to cancel replay and go back to the list.
        if (IsKeyPressed(KEY_F)) {
            m_inReplay = false;
            m_replaySystem.reset();
            // Reload saved games
            loadSavedGames();
        }
    }
}

void ReplayScreen::update() {
    // When in replay mode, update replay system.
    if (m_inReplay && m_replaySystem) {
        m_replaySystem->advanceFrame();
        // Optionally, if replay playback is complete, return to list.
        if (m_replaySystem->isPlaybackFinished()) {
            m_inReplay = false;
            m_replaySystem.reset();
            loadSavedGames();
        }
    }
}

void ReplayScreen::render() {
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));

    if (!m_inReplay) {
        // Display the list of saved games.
        DrawTextEx(GetFontDefault(), "Select a Saved Game: (Enter to replay, F to go back)",
                   {100, 50}, 20, 1, WHITE);
        float startY = 100.0f;
        for (size_t i = 0; i < m_savedGames.size(); i++) {
            Color color = (i == static_cast<size_t>(m_selectedIndex)) ? RED : WHITE;
            DrawTextEx(GetFontDefault(), m_savedGames[i].c_str(), {100, startY + i * 30}, 20, 1, color);
        }
    }
    else {
        // In replay mode, render the replay.
        if (m_replaySystem) {
            const ReplayFrame &frame = m_replaySystem->getCurrentFrame();
            DrawCircleV(frame.characterPosition, 10, RED);
            for (const auto &platformPos : frame.platformPositions) {
                DrawRectangleV(platformPos, {100, 20}, GRAY);
            }
            // Display instructions to return.
            DrawTextEx(GetFontDefault(), "Press F to exit replay", {100, 20}, 20, 1, YELLOW);
        }
    }

    EndDrawing();
}