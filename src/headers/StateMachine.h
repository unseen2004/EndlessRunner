#pragma once
#include <memory>
#include <iostream>
#include "State.h"

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
