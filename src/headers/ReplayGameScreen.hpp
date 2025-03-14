#ifndef REPLAYGAMESCREEN_HPP
#define REPLAYGAMESCREEN_HPP

#include <string>
#include "GameScreen.hpp"


class ReplayGameScreen : public GameScreen {
public:
    ReplayGameScreen(StateMachine &sm, const std::string &replayFile);

    ~ReplayGameScreen();

    void handleInput();

    void update();

    void render();

    [[nodiscard]] virtual const char *getName() const { return "ReplayGameScreen"; }

private:
    bool m_replayFinished = false;
};

#endif // REPLAYGAMESCREEN_HPP
