#include "../headers/StateMachine.hpp"
#include "../headers/DebugLog.hpp"

auto StateMachine::changeState(std::unique_ptr<State> newState) -> void { pendingState = std::move(newState); }

auto StateMachine::processPendingState() -> void {
    if (pendingState) {
        LOG("Changing state");
        currentState = std::move(pendingState);
    }
}

auto StateMachine::handleInput() -> void {
    if (currentState)
        currentState->handleInput();
}

auto StateMachine::update() -> void {
    if (currentState)
        currentState->update();
}

auto StateMachine::render() -> void {
    if (currentState)
        currentState->render();
}
