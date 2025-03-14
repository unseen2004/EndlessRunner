#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <memory>
#include "State.hpp"

class StateMachine {
public:
    auto changeState(std::unique_ptr<State> newState) -> void;

    auto processPendingState() -> void;

    auto handleInput() -> void;

    auto update() -> void;

    auto render() -> void;

private:
    std::unique_ptr<State> currentState = nullptr;
    std::unique_ptr<State> pendingState = nullptr;
};

#endif // STATEMACHINE_HPP
