#ifndef REPLAYSCREEN_HPP
#define REPLAYSCREEN_HPP

#include <vector>
#include <string>
#include <utility>
#include "raylib.h"
#include <filesystem>
#include <iostream>
#include "State.hpp"
#include "StateMachine.hpp"


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
    std::vector<std::pair<std::string, std::string> > m_savedGames;
    int m_selectedIndex;
    bool m_inReplay;

    void loadSavedGames();

    void startReplay(const std::string &filename);
};

#endif // REPLAYSCREEN_HPP
