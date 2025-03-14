#ifndef REPLAYGAMESCREEN_HPP
#define REPLAYGAMESCREEN_HPP

#include <string>
#include "GameScreen.hpp"

class ReplayGameScreen : public GameScreen {
public:
    ReplayGameScreen(StateMachine &sm, const std::string &replayFile);
    ~ReplayGameScreen();

    auto handleInput() -> void;
    auto update() -> void;
    auto render() -> void;
    [[nodiscard]] auto getName() const -> const char* { return "ReplayGameScreen"; }

private:
    bool m_replayFinished = false;
};

#endif
