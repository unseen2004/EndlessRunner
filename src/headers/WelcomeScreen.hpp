#ifndef WELCOMESCREEN_HPP
#define WELCOMESCREEN_HPP

#include "raylib.h"
#include "State.hpp"
#include "StateMachine.hpp"
#include "GameScreen.hpp"
#include "ReplayScreen.hpp"

class WelcomeScreen : public State {
    StateMachine &stateMachine;
    float m_animationTimer;

public:
    WelcomeScreen(StateMachine &sm);

    ~WelcomeScreen();

    void handleInput() override;

    void update() override;

    void render() override;

    const char *getName() const override { return "WelcomeScreen"; }
};

#endif // WELCOMESCREEN_HPP
