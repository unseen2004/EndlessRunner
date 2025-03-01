#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "State.h"
#include "StateMachine.h"
#include "raylib.h"
#include "DeadScreen.h"
#include "Background.h"
#include "Character.h"
#include "Cloud.h"
#include "Random.h"
#include <vector>
#include <memory>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "Platform.h"
#include "Config.h"

namespace fs = std::filesystem;

class GameScreen : public State {
    StateMachine& m_stateMachine;
    std::unique_ptr<Background> m_bg_background;
    std::unique_ptr<Background> m_bg_foreground;
    std::unique_ptr<Background> m_bg_midground;
    std::unique_ptr<Background> m_bg_sky;
    std::unique_ptr<Character> m_character;
    float m_speed;
    bool m_input_jump;
    bool m_input_dash;
    std::chrono::time_point<std::chrono::steady_clock> m_startTime;
    std::vector<std::unique_ptr<Cloud>> m_clouds;
    std::vector<std::unique_ptr<Platform>> m_platforms_bottom{};
    std::vector<std::unique_ptr<Platform>> m_platforms_top{};

public:
    explicit GameScreen(StateMachine& sm);
    ~GameScreen() override;

    void handleInput() override;
    void update() override;
    void render() override;


private:
    void updateSpeedBasedOnTime(std::chrono::steady_clock::time_point start_time);
    void spawnClouds();
    void spawnPlatforms(std::vector<std::unique_ptr<Platform>>& platform, bool bottom);
};

#endif // GAMESCREEN_H