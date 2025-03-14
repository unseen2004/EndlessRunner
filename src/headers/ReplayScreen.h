// Language: cpp
// File: src/headers/ReplayScreen.h
#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <memory>
#include "State.h"
#include "StateMachine.h"
#include "ReplaySystem.h"
#include "raylib.h"

namespace fs = std::filesystem;

class ReplayScreen : public State {
public:
    ReplayScreen(StateMachine &sm);
    ~ReplayScreen();

    void handleInput() override;
    void update() override;
    void render() override;
    const char *getName() const override { return "ReplayScreen"; }

private:
    StateMachine &m_stateMachine;
    std::unique_ptr<ReplaySystem> m_replaySystem;

    // List view fields
    std::vector<std::string> m_savedGames;
    int m_selectedIndex = 0;
    bool m_inReplay = false;

    // Helper functions
    void loadSavedGames();
    void startReplay(const std::string &filename);
};;