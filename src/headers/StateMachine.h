#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <memory>
#include "State.h"


class StateMachine {
private:
    std::unique_ptr<State> currentState;

public:
    // Change the current state.
    void changeState(std::unique_ptr<State> newState);

    // Delegates input handling to the current state.
    void handleInput();

    // Delegates update logic to the current state.
    void update();

    // Delegates rendering to the current state.
    void render();
};

#endif // STATEMACHINE_H

