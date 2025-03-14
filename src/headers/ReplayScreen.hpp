#ifndef REPLAYSCREEN_HPP
#define REPLAYSCREEN_HPP

#include <filesystem>
#include <string>
#include <utility>
#include <vector>
#include "State.hpp"
#include "StateMachine.hpp"
#include "raylib.h"

class ReplayScreen : public State {
public:
    ReplayScreen(StateMachine &sm);

    ~ReplayScreen();

    auto handleInput() -> void override;

    auto update() -> void override;

    auto render() -> void override;

    [[nodiscard]] auto getName() const -> const char * override { return "ReplayScreen"; }

private:
    StateMachine &m_stateMachine;
    std::vector<std::pair<std::string, std::string>> m_savedGames;
    int m_selectedIndex;
    bool m_inReplay;

    auto loadSavedGames() -> void;

    auto startReplay(const std::string &filename) -> void;
};

#endif
