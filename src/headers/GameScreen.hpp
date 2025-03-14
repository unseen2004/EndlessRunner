#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include <vector>
#include <memory>
#include <chrono>
#include <filesystem>
#include <algorithm>
#include "raylib.h"
#include "Background.hpp"
#include "Platform.hpp"
#include "Cloud.hpp"
#include "DeadScreen.hpp"
#include "StateMachine.hpp"
#include "Character.hpp"
#include "Star.hpp"
#include "Interface.hpp"
#include "Snow.hpp"
#include "StarPopout.hpp"
#include "ReplaySystem.hpp"
#include "State.hpp"

namespace fs = std::filesystem;


class GameScreen : public State {
public:
    GameScreen(StateMachine &sm);

    virtual ~GameScreen();

    virtual void handleInput() override;

    virtual void update() override;

    virtual void render() override;

    virtual const char *getName() const override { return "GameScreen"; }

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
    std::vector<std::unique_ptr<Star> > m_stars;
    std::vector<std::unique_ptr<StarPopout> > m_popouts;
    const char *text = "+1 ポイント";
    Font font;
    float m_invulnerability_timer = 0.5F;
    static bool s_invulnerability_active;

    std::chrono::steady_clock::time_point m_startTime;

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

#endif // GAMESCREEN_HPP
