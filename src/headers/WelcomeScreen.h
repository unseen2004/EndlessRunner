// Language: cpp
// File: `src/headers/WelcomeScreen.h`
#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include "State.h"
#include "raylib.h"
#include "StateMachine.h"
#include "GameScreen.h"
#include "ReplayScreen.h"

class WelcomeScreen : public State {
    StateMachine &stateMachine;
    float m_animationTimer; // for text animation

public:
    WelcomeScreen(StateMachine &sm);

    ~WelcomeScreen();

    void handleInput() override;

    void update() override;

    void render() override;

    const char *getName() const override { return "WelcomeScreen"; }
};

#endif // WELCOMESCREEN_H
