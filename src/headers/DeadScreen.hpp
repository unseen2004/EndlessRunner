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

    void handleInput() override;

    void update() override;

    void render() override;

    const char *getName() const override { return "DeadScreen"; }
};

#endif // DEADSCREEN_HPP
