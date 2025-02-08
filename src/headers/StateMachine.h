#pragma once

#include <memory>
#include <unordered_map>
#include <string>

class State {
public:
    virtual ~State() = default;
    virtual void update() = 0;
    virtual void draw() = 0;
};

class StateMachine {
public:
    void addState(const std::string &name, std::unique_ptr<State> state);
    void changeState(const std::string &name);
    void update();
    void draw();

private:
    std::unordered_map<std::string, std::unique_ptr<State>> states;
    State *currentState = nullptr;
};