#pragma once

#include "StateMachine.h"
#include "raylib.h"
#include <memory>
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    StateMachine stateMachine;
    void init();
    void loadResources();
    void unloadResources();

    std::unique_ptr<Background> bg_background;
    std::unique_ptr<Background> bg_foreground;
    std::unique_ptr<Background> bg_midground;
    std::unique_ptr<Background> bg_sky;
    std::unique_ptr<Character> character;
    std::vector<std::unique_ptr<Cloud>> clouds;
};