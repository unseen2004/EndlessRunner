#ifndef GAME_HPP
#define GAME_HPP

#include "Config.hpp"
#include "StateMachine.hpp"
#include "WelcomeScreen.hpp"

class Game {
private:
    StateMachine m_stateMachine;

public:
    Game();

    ~Game();

    auto run() -> void;
};

#endif // GAME_HPP
