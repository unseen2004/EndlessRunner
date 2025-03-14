#pragma once

#include <vector>
#include <memory>
#include <chrono>
#include <map>
#include <iostream>
#include <filesystem>
#include <algorithm>

#include "raylib.h"
#include "Background.h"
#include "Platform.h"
#include "Cloud.h"
#include "Random.h"
#include "DeadScreen.h"
#include "StateMachine.h"
#include "Config.h"
#include "Character.h"
#include "Star.hpp"
#include "Interface.h"
#include "Snow.h"
#include "StarPopout.h"
#include "ReplaySystem.h"
#include "ReplayScreen.h"


#include "raylib.h"
#include <filesystem>
#include <iostream>

#include "WelcomeScreen.h"

namespace fs = std::filesystem;

class StateMachine;
class DeadScreen;

class GameScreen : public State {
public:
    GameScreen(StateMachine &sm);

    ~GameScreen();

    void handleInput() override;

    void update() override;

    void render() override;

    const char *getName() const override { return "GameScreen"; }
    bool m_input_jump = false;
    bool m_input_dash = false;

    StateMachine &m_stateMachine;
    bool replay = false;

private:
    // Game state
    float m_speed = 1.0f;
    bool m_game_over = false;
    float m_death_timer = 0.0f;
    float m_death_delay = 2.0f;
    std::vector<std::unique_ptr<Star> > m_stars;
    std::vector<std::unique_ptr<StarPopout> > m_popouts;
    const char *text = "+1 ポイント";
    Font font;
    // Invulnerability timer for game start
    float m_invulnerability_timer = 0.5f;
    static bool s_invulnerability_active;
    std::unique_ptr<ReplaySystem> m_replaySystem; // Replay system instance

    // Input state

    // Game time tracking
    std::chrono::steady_clock::time_point m_startTime;

    // Game objects
    std::unique_ptr<Background> m_bg_background;
    std::unique_ptr<Background> m_bg_foreground;
    std::unique_ptr<Background> m_bg_midground;
    std::unique_ptr<Background> m_bg_sky;
    std::vector<std::unique_ptr<Cloud> > m_clouds;
    std::vector<std::unique_ptr<Platform> > m_platforms_bottom;
    std::vector<std::unique_ptr<Platform> > m_platforms_top;
    std::unique_ptr<Character> m_character;
    int m_stars_collected = 0;
    std::unique_ptr<Interface> m_interface;
    std::unique_ptr<Snow> m_snow;

    void spawnStars();

    void handleDeathTransition();

    bool isDeadAnimationFinished();

    void spawnClouds();

    void spawnPlatforms(std::vector<std::unique_ptr<Platform> > &platform, bool bottom);

    void updateSpeedBasedOnTime(std::chrono::steady_clock::time_point start_time);
};
