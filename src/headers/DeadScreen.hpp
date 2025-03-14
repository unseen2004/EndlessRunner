#ifndef DEADSCREEN_HPP
#define DEADSCREEN_HPP

#include "State.hpp"
#include "StateMachine.hpp"
#include "WelcomeScreen.hpp"

class DeadScreen : public State {
    StateMachine &stateMachine;

public:
    DeadScreen(StateMachine &sm);

    ~DeadScreen();

    auto handleInput() -> void override;

    auto update() -> void override;

    auto render() -> void override;

    auto getName() const -> const char * override { return "DeadScreen"; }
};

#endif
