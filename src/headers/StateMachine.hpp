#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <iostream>
#include <memory>
#include "State.hpp"

class StateMachine {
public:
    void changeState(std::unique_ptr<State> newState);

    void processPendingState();

    void handleInput();

    void update();

    void render();

private:
    std::unique_ptr<State> currentState = nullptr;
    std::unique_ptr<State> pendingState = nullptr;
};

#endif // STATEMACHINE_HPP
