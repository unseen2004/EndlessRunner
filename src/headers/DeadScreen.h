#ifndef DEADSCREEN_H
#define DEADSCREEN_H

#include "State.h"
#include "StateMachine.h"
#include "raylib.h"
#include "WelcomeScreen.h"

class DeadScreen : public State {
    StateMachine& stateMachine;
public:
    DeadScreen(StateMachine& sm);
    ~DeadScreen();

    void handleInput() override;
    void update() override;
    void render() override;
};

#endif // DEADSCREEN_H

