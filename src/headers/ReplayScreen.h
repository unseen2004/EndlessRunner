//
// Created by maks on 3/14/25.
//

#ifndef REPLAYSCREEN_H
#define REPLAYSCREEN_H
#include "State.h"
#include "raylib.h"
#include "StateMachine.h"
#include "WelcomeScreen.h"
class ReplayScreen : public State {
    StateMachine &stateMachine;

public:
    ReplayScreen(StateMachine &sm);

    ~ReplayScreen();

    void handleInput() override;

    void update() override;

    void render() override;

    const char *getName() const override { return "ReplayScreen"; }
};
#endif //REPLAYSCREEN_HPP
