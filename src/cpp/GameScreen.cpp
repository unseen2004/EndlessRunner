#include "../headers/GameScreen.h"

bool GameScreen::s_invulnerability_active = false;

GameScreen::GameScreen(StateMachine& sm) : m_stateMachine(sm) {
    m_invulnerability_timer = 0.5f;
    s_invulnerability_active = true;

    try {
        m_bg_background = std::make_unique<Background>(fs::path("resources/background/BG.png"), m_speed);
        if (!m_bg_background) throw std::runtime_error("Failed to load background");

        m_bg_foreground = std::make_unique<Background>(fs::path("resources/background/FG.png"), m_speed);
        if (!m_bg_foreground) throw std::runtime_error("Failed to load foreground");

        m_bg_midground = std::make_unique<Background>(fs::path("resources/background/MG.png"), m_speed);
        if (!m_bg_midground) throw std::runtime_error("Failed to load midground");

        m_bg_sky = std::make_unique<Background>(fs::path("resources/background/Sky.png"), m_speed);
        if (!m_bg_sky) throw std::runtime_error("Failed to load sky");


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    m_startTime = std::chrono::steady_clock::now();
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetTargetFPS(config::FRAMES);
}

GameScreen::~GameScreen() {
    // Clean up resources
    m_bg_background.reset();
    m_bg_foreground.reset();
    m_bg_midground.reset();
    m_bg_sky.reset();
}

void GameScreen::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        m_stateMachine.changeState(std::make_unique<DeadScreen>(m_stateMachine));
    }

    // Store input state for future implementation
    m_input_jump = IsKeyPressed(KEY_SPACE);
    m_input_dash = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
}

void GameScreen::updateSpeedBasedOnTime(std::chrono::steady_clock::time_point start_time) {
    auto currentTime = std::chrono::steady_clock::now();
    auto diff = currentTime - start_time;

    if (m_game_over) {
        m_speed = 0.0f;
    } else {
        // Gradually increase speed over time
        m_speed = 1.0f + config::e * std::chrono::duration_cast<std::chrono::seconds>(diff).count();
    }

    // Update all object speeds
    m_bg_background->changeSpeed(m_speed);
    m_bg_foreground->changeSpeed(m_speed);
    m_bg_midground->changeSpeed(m_speed);
    m_bg_sky->changeSpeed(m_speed);

    for (auto &cloud: m_clouds) {
        cloud->changeSpeed(m_speed);
    }

    for (auto &platform: m_platforms_bottom) {
        platform->changeSpeed(m_speed);
    }

    for (auto &platform: m_platforms_top) {
        platform->changeSpeed(m_speed);
    }
}

void GameScreen::spawnClouds() {
    if (m_clouds.size() < config::MAX_CLOUDS) {
        int lastX = m_clouds.empty() ? 0 : m_clouds.back()->getX();

        // Ensure the last cloud is far enough before spawning a new one
        if (m_clouds.empty() || lastX < config::SCREEN_WIDTH - config::PLATFORM_WIDTH) {
            try {
                int spawnY = Random::get(0, 100);
                m_clouds.push_back(std::make_unique<Cloud>(
                    fs::path("resources/clouds/Cloud_" + std::to_string(Random::get(1, 3)) + ".png"),
                    m_speed, Random::get(1.0f, 2.0f), config::SCREEN_WIDTH, spawnY, Random::get(0.3f, 0.5f)));
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
}

void GameScreen::spawnPlatforms(std::vector<std::unique_ptr<Platform>>& platform, bool bottom) {
    if (platform.size() < config::MAX_PLATFORMS) {
        int lastX = platform.empty() ? 0 : platform.back()->getX();

        // Ensure the last platform is far enough before spawning a new one
        if (bottom && (platform.empty() || lastX < config::SCREEN_WIDTH - config::PLATFORM_WIDTH * 2) ||
            !bottom && (platform.empty() || lastX < config::SCREEN_WIDTH - config::PLATFORM_WIDTH*4)) {
            try {
                int spawnY;
                if (bottom) {
                    spawnY = Random::get(700, config::SCREEN_HEIGHT - 300);
                } else {
                    spawnY = Random::get(0, 100);
                }

                bool has_obstacle = Random::get(0, 10) < 7; // 70% chance to have obstacle
                platform.push_back(std::make_unique<Platform>(
                    has_obstacle, m_speed, config::SCREEN_WIDTH, spawnY, 1.0f));

            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
}

void GameScreen::update() {
    if (m_invulnerability_timer > 0) {
        m_invulnerability_timer -= GetFrameTime();
        s_invulnerability_active = true;
    } else {
        s_invulnerability_active = false;
    }

    // Check for user input
    handleInput();

    // Skip updates if game is over
    if (m_game_over) {
        m_death_timer += GetFrameTime();
        if (m_death_timer > m_death_delay) {
            m_stateMachine.changeState(std::make_unique<DeadScreen>(m_stateMachine));
        }
        return;
    }

    // Update game speed
    updateSpeedBasedOnTime(m_startTime);

    // Spawn new objects
    spawnClouds();
    spawnPlatforms(m_platforms_bottom, true);
    spawnPlatforms(m_platforms_top, false);

    // Update clouds and remove off-screen ones
    m_clouds.erase(
        std::remove_if(
            m_clouds.begin(), m_clouds.end(),
            [](const std::unique_ptr<Cloud>& cloud) -> bool {
                return !cloud->update();
            }
        ),
        m_clouds.end()
    );

    // Update bottom platforms and remove off-screen ones
    m_platforms_bottom.erase(
        std::remove_if(
            m_platforms_bottom.begin(), m_platforms_bottom.end(),
            [](const std::unique_ptr<Platform>& platform) -> bool {
                return !platform->update();
            }
        ),
        m_platforms_bottom.end()
    );

    // Update top platforms and remove off-screen ones
    m_platforms_top.erase(
        std::remove_if(
            m_platforms_top.begin(), m_platforms_top.end(),
            [](const std::unique_ptr<Platform>& platform) -> bool {
                return !platform->update();
            }
        ),
        m_platforms_top.end()
    );

    // Update backgrounds
    m_bg_background->update();
    m_bg_foreground->update();
    m_bg_midground->update();
    m_bg_sky->update();
}

void GameScreen::render() {
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));

    // Draw backgrounds with parallax effect
    m_bg_sky->draw(m_bg_sky->getX());
    m_bg_sky->draw(m_bg_sky->getWidth() * 2 + m_bg_sky->getX());

    m_bg_background->draw(m_bg_background->getX());
    m_bg_background->draw(m_bg_background->getWidth() * 2 + m_bg_background->getX());

    m_bg_midground->draw(m_bg_midground->getX());
    m_bg_midground->draw(m_bg_midground->getWidth() * 2 + m_bg_midground->getX());

    m_bg_foreground->draw(m_bg_foreground->getX());
    m_bg_foreground->draw(m_bg_foreground->getWidth() * 2 + m_bg_foreground->getX());

    // Draw clouds
    for (auto &cloud: m_clouds) {
        cloud->draw();
    }

    // Draw bottom platforms and their obstacles
    for (auto &platform: m_platforms_bottom) {
        platform->draw();
    }

    // Draw top platforms and their obstacles
    for (auto &platform: m_platforms_top) {
        platform->draw();
    }

    // Draw FPS counter and game info
    DrawText(TextFormat("SPEED: %.1f", m_speed), 20, 20, 20, GREEN);
    DrawText(TextFormat("FPS: %i", (int)(1.0f/GetFrameTime())), 20, 50, 20, GREEN);

    // Draw controls hint
    DrawText("SPACE: Jump (Double Jump Available)", config::SCREEN_WIDTH - 320, 20, 16, GREEN);
    DrawText("SHIFT: Dash", config::SCREEN_WIDTH - 320, 40, 16, GREEN);

    if (m_game_over) {
        DrawText("GAME OVER!", config::SCREEN_WIDTH/2 - 100, config::SCREEN_HEIGHT/2 - 50, 40, RED);
    }

    EndDrawing();
}