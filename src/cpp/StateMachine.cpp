#include "StateMachine.h"

void StateMachine::addState(const std::string &name, std::unique_ptr<State> state) {
    states[name] = std::move(state);
}

void StateMachine::changeState(const std::string &name) {
    auto it = states.find(name);
    if (it != states.end()) {
        currentState = it->second.get();
    }
}

void StateMachine::update() {
    if (currentState) {
        currentState->update();
    }
}

void StateMachine::draw() {
    if (currentState) {
        currentState->draw();
    }
}