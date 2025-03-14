// File: src/headers/ReplayScreen.h
#pragma once
#include <vector>
#include <string>
#include <utility>
#include "State.h"
#include "StateMachine.h"

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
    std::vector<std::pair<std::string, std::string>> m_savedGames; // first: filename, second: display name
    int m_selectedIndex;
    bool m_inReplay;

    void loadSavedGames();
    void startReplay(const std::string &filename);
};