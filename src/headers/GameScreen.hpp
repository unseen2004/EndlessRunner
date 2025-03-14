#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <memory>
#include <vector>
#include "Background.hpp"
#include "Character.hpp"
#include "Cloud.hpp"
#include "DeadScreen.hpp"
#include "Interface.hpp"
#include "Platform.hpp"
#include "ReplaySystem.hpp"
#include "Snow.hpp"
#include "Star.hpp"
#include "StarPopout.hpp"
#include "State.hpp"
#include "StateMachine.hpp"
#include "raylib.h"

namespace fs = std::filesystem;

class GameScreen : public State {
public:
    GameScreen(StateMachine &sm);

    virtual ~GameScreen();

    auto handleInput() -> void override;

    auto update() -> void override;

    auto render() -> void override;

    auto getName() const -> const char * override { return "GameScreen"; }

protected:
    StateMachine &m_stateMachine;
    bool replay = false;
    bool m_input_jump = false;
    bool m_input_dash = false;
    std::unique_ptr<ReplaySystem> m_replaySystem;

private:
    float m_speed = 10.0F;
    bool m_game_over = false;
    float m_death_timer = 0.0F;
    float m_death_delay = 2.0F;
    std::vector<std::unique_ptr<Star>> m_stars;
    std::vector<std::unique_ptr<StarPopout>> m_popouts;
    const char *text = "+1 ポイント";
    Font font;
    float m_invulnerability_timer = 0.5F;
    std::chrono::steady_clock::time_point m_startTime;
    std::unique_ptr<Background> m_bg_background;
    std::unique_ptr<Background> m_bg_foreground;
    std::unique_ptr<Background> m_bg_midground;
    std::unique_ptr<Background> m_bg_sky;
    std::vector<std::unique_ptr<Cloud>> m_clouds;
    std::vector<std::unique_ptr<Platform>> m_platforms_bottom;
    std::vector<std::unique_ptr<Platform>> m_platforms_top;
    std::unique_ptr<Character> m_character;
    int m_stars_collected = 0;
    std::unique_ptr<Interface> m_interface;
    std::unique_ptr<Snow> m_snow;

    void spawnStars();

    void handleDeathTransition();

    bool isDeadAnimationFinished();

    void spawnClouds();

    void spawnPlatforms(std::vector<std::unique_ptr<Platform>> &platforms, bool bottom);

    void updateSpeedBasedOnTime(std::chrono::steady_clock::time_point start_time);
};

#endif // GAMESCREEN_HPP
