#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include "State.h"
#include "raylib.h"
#include "StateMachine.h"
#include "GameScreen.h"

class WelcomeScreen : public State {
    StateMachine& stateMachine;
public:
    WelcomeScreen(StateMachine& sm);
    ~WelcomeScreen();

    void handleInput() override;
    void update() override;
    void render() override;
};

#endif // WELCOMESCREEN_H