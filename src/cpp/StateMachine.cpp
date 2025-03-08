#include "../headers/StateMachine.h"

void StateMachine::changeState(std::unique_ptr<State> newState) {
    // Instead of switching state immediately, store it as pending
    pendingState = std::move(newState);
}

void StateMachine::processPendingState() {
    if (pendingState) {
        std::cout << "Changing state from "
                  << (currentState ? currentState->getName() : "nullptr")
                  << " to " << pendingState->getName() << std::endl;
        currentState = std::move(pendingState);
    }
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