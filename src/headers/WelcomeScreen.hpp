#ifndef WELCOMESCREEN_HPP
#define WELCOMESCREEN_HPP

#include "GameScreen.hpp"
#include "ReplayScreen.hpp"
#include "State.hpp"
#include "StateMachine.hpp"
#include "raylib.h"

class WelcomeScreen : public State {
    StateMachine &stateMachine;
    float m_animationTimer;

public:
    WelcomeScreen(StateMachine &sm);

    ~WelcomeScreen();

    auto handleInput() -> void override;

    auto update() -> void override;

    auto render() -> void override;

    auto getName() const -> const char * override { return "WelcomeScreen"; }
};

#endif // WELCOMESCREEN_HPP
