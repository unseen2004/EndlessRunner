#ifndef GAME_HPP
#define GAME_HPP

#include "StateMachine.hpp"
#include "WelcomeScreen.hpp"
#include "Config.hpp"

class Game {
    StateMachine m_stateMachine;

public:
    Game();

    ~Game();

    void run();
};

#endif // GAME_HPP