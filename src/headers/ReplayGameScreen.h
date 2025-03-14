// File: src/headers/ReplayGameScreen.h
#pragma once

#include "GameScreen.h"
#include "ReplaySystem.h"

class ReplayGameScreen : public GameScreen {
public:
    ReplayGameScreen(StateMachine &sm, const std::string &replayFile);
    ~ReplayGameScreen() override;

    void handleInput() override;
    void update() override;
    void render() override;

    const char *getName() const override { return "ReplayGameScreen"; }

private:
    std::unique_ptr<ReplaySystem> m_replaySystem;
    bool m_replayFinished = false;
};