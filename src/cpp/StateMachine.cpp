#include "../headers/StateMachine.h"

void StateMachine::changeState(std::unique_ptr<State> newState) {
    currentState = std::move(newState);
}

void StateMachine::handleInput() {
    if (currentState)
        currentState->handleInput();
}

void StateMachine::update() {
    if (currentState)
        currentState->update();
}

void StateMachine::render() {
    if (currentState)
        currentState->render();
}