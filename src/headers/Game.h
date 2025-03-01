#ifndef GAME_H
#define GAME_H

#include "StateMachine.h"
#include "WelcomeScreen.h"
#include "Config.h"

class Game {
    StateMachine m_stateMachine;
public:

    Game();
    ~Game();

    void run();
};

#endif // GAME_H
