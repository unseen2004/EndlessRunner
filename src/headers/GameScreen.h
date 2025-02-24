#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "State.h"
#include "StateMachine.h"
#include "raylib.h"
#include "DeadScreen.h"

class GameScreen : public State {
    StateMachine& stateMachine;
public:
    GameScreen(StateMachine& sm);
    ~GameScreen();

    void handleInput() override;
    void update() override;
    void render() override;
};

#endif // GAMESCREEN_H