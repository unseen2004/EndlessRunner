#include "../headers/StateMachine.hpp"
#include "../headers/DebugLog.hpp"

void StateMachine::changeState(std::unique_ptr<State> newState) {
    // Instead of switching state immediately, store it as pending
    pendingState = std::move(newState);
}

void StateMachine::processPendingState() {
    if (pendingState) {
        LOG("Changing state from "
            << (currentState ? currentState->getName() : "nullptr")
            << " to " << pendingState->getName());
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