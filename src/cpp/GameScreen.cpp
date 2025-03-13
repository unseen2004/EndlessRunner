#include "../headers/GameScreen.h"

bool GameScreen::s_invulnerability_active = false;

GameScreen::GameScreen(StateMachine &sm) : m_stateMachine(sm) {
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

        m_character = std::make_unique<Character>(fs::path("resources/scarfy.png"),
                                                   fs::path("resources/explosion.png"),
                                                   fs::path("resources/sound/boom.wav"), m_speed);
        if (!m_character) throw std::runtime_error("Failed to load character");

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    float platformX = 300;
    float platformY = 300;
    m_platforms_bottom.push_back(std::make_unique<Platform>(
         m_speed, platformX, platformY, 1.0f));

    m_platforms_bottom.push_back(std::make_unique<Platform>(
         m_speed, platformX+600, platformY, 1.0f));
    m_startTime = std::chrono::steady_clock::now();
    if (config::snow) {
        m_snow = std::make_unique<Snow>(100, config::SCREEN_WIDTH, config::SCREEN_HEIGHT);
    }
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetTargetFPS(config::FRAMES);
}

GameScreen::~GameScreen() {
    m_bg_background.reset();
    m_bg_foreground.reset();
    m_bg_midground.reset();
    m_bg_sky.reset();
    m_character.reset();
    m_interface.reset();
    for(auto &cloud : m_clouds) {
        cloud.reset();
    }
    for(auto &platform : m_platforms_bottom) {
        platform.reset();
    }
    for(auto &platform : m_platforms_top) {
        platform.reset();
    }
    for(auto &star : m_stars) {
        star.reset();
    }
    m_snow.reset();
}
// File: src/cpp/GameScreen.cpp
// This helper function stops other world updates and only processes the character’s death animation.
// Once finished, it transitions to the next game screen.
// Language: cpp
// File: src/cpp/GameScreen.cpp

void GameScreen::handleDeathTransition() {
    // Update the dead animation of the character.
    m_character->updateDeadAnimation();

    // When the explosion animation finishes, change state.
    if (m_character->isDeadAnimationFinished()) {
        m_stateMachine.changeState(std::make_unique<DeadScreen>(m_stateMachine));
    }
}
void GameScreen::handleInput() {
    if (IsKeyPressed(KEY_ENTER) && !m_character->isAlive()) {
        m_stateMachine.changeState(std::make_unique<DeadScreen>(m_stateMachine));
    }
    m_input_jump = IsKeyPressed(KEY_SPACE);
    m_input_dash = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
}

void GameScreen::updateSpeedBasedOnTime(std::chrono::steady_clock::time_point start_time) {
    auto currentTime = std::chrono::steady_clock::now();
    auto diff = currentTime - start_time;
    if (m_game_over) {
        m_speed = 0.0f;
    } else {
            	m_speed = 1.0f + config::e * std::chrono::duration_cast<std::chrono::seconds>(diff).count();

    }
    m_bg_background->changeSpeed(m_speed);
    m_bg_foreground->changeSpeed(m_speed);
    m_bg_midground->changeSpeed(m_speed);
    m_bg_sky->changeSpeed(m_speed);
    m_character->changeSpeed(m_speed);
    for (auto &cloud : m_clouds) {
        cloud->changeSpeed(m_speed);
    }
    for (auto &platform : m_platforms_bottom) {
        platform->changeSpeed(m_speed);
        auto it = m_obstacles.find(platform.get());
        if (it != m_obstacles.end() && it->second) {
            it->second->changeSpeed(m_speed);
        }
    }
    for (auto &platform : m_platforms_top) {
        platform->changeSpeed(m_speed);
        auto it = m_obstacles.find(platform.get());
        if (it != m_obstacles.end() && it->second) {
            it->second->changeSpeed(m_speed);
        }
    }
}

void GameScreen::spawnClouds() {//usun randomval
    if (m_clouds.size() < config::MAX_CLOUDS) {
        int lastX = m_clouds.empty() ? 0 : m_clouds.back()->getX();

        // Ensure the last cloud is far enough before spawning a new one
        if (m_clouds.empty() || lastX < config::SCREEN_WIDTH - config::PLATFORM_WIDTH) {
            try {
                int spawnY = Random::get(0, 100);
                m_clouds.push_back(std::make_unique<Cloud>(fs::path("resources/clouds/Cloud_" + std::to_string(Random::get(1, 3)) + ".png"), m_speed, Random::get(1.0f, 2.0f), config::SCREEN_WIDTH, spawnY, Random::get(0.3f, 0.5f)));

            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
}
    // ---------- Handle Stars ----------

    // Spawn stars if below maximum count.
// File: `src/cpp/GameScreen.cpp`
void GameScreen::spawnStars() {
    // Only attempt to spawn if we have fewer than the maximum stars,
    // and use a random chance (e.g., 10% chance) each update frame.
    if (m_stars.size() < config::MAX_STARS && GetRandomValue(0, 100) < 5) {
        // Define spawn area starting out of screen to the right.
        // x starts at SCREEN_WIDTH, and spawnWidth is an extra margin.
        float spawnX = static_cast<float>(config::SCREEN_WIDTH);
        float spawnWidth = 300.0f; // extra margin
        Rectangle spawnArea = { spawnX, 0, spawnWidth, static_cast<float>(config::SCREEN_HEIGHT) };

        // Star::SpawnRandom checks against platforms to avoid collisions.
        Star* newStar = Star::SpawnRandom(spawnArea, m_platforms_bottom);
        if (newStar) {
            m_stars.push_back(std::unique_ptr<Star>(newStar));
        }
    }
}
    // Update stars and check collision with the character.


    // ---------- End Stars ----------
void GameScreen::spawnPlatforms(std::vector<std::unique_ptr<Platform>>& platforms, bool bottom) {
    if (platforms.size() < config::MAX_PLATFORMS) {
        int lastX = platforms.empty() ? 0 : platforms.back()->getX();
        if ((bottom && (platforms.empty() || lastX < config::SCREEN_WIDTH - config::PLATFORM_WIDTH * 2)) ||
            (!bottom && (platforms.empty() || lastX < config::SCREEN_WIDTH - config::PLATFORM_WIDTH * 4))) {
            try {
                int spawnY = bottom ? Random::get(700, config::SCREEN_HEIGHT - 300) : Random::get(0, 100);
                // Create a new platform before adding to the vector.
                auto newPlatform = std::make_unique<Platform>(m_speed, config::SCREEN_WIDTH, spawnY, 1.0f);
                // Now create an obstacle for this platform if needed.
                if (Random::get(0, 10) < 30) {
                    m_obstacles[newPlatform.get()] = std::make_unique<Obstacle>(*newPlatform, m_speed, Random::get(2, 4));
                }
                // Push the platform into the vector.
                platforms.push_back(std::move(newPlatform));
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
}

void GameScreen::update() {
    handleInput();
    if (!m_character->isAlive()) {
        handleDeathTransition();
        return;
    }
       if (config::snow && m_snow) {
        m_snow->update();
    }
    updateSpeedBasedOnTime(m_startTime);
    spawnClouds();
    spawnPlatforms(m_platforms_bottom, true);
    spawnPlatforms(m_platforms_top, false);
    spawnStars();
    m_character->update(m_input_jump, m_input_dash, m_platforms_bottom, m_platforms_top);
    for (auto it = m_obstacles.begin(); it != m_obstacles.end(); ) {
        if (m_character->checkObstacleCollision(*it->second)) {
            if (m_character->isDashing()) {
                // If dashing, destroy the obstacle.
                it = m_obstacles.erase(it);
                continue;
            } else {
                // If not dashing, kill the character.
                m_character->kill();
                break;
            }
        }
        ++it;
    }
       Rectangle characterRect = m_character->getCollisionRect();
for (auto it = m_stars.begin(); it != m_stars.end(); ) {
    (*it)->update();
    // Move the star with the current game speed and dash boost.
    (*it)->applyMovement(m_speed + m_character->getDashBoost(GetFrameTime()));
    if (CheckCollisionRecs(m_character->getCollisionRect(), (*it)->getBoundingBox())) {
        m_stars_collected++;
        it = m_stars.erase(it);
    } else {
        ++it;
    }
}
    // Apply dash boost to world objects when dashing.
    float dt = GetFrameTime();
    float dashBoost = m_character->getDashBoost(dt);
    if (dashBoost > 0) {
        for (auto &cloud : m_clouds) {
            cloud->applyDashBoost(dashBoost);
        }
        for (auto &platform : m_platforms_bottom) {
            platform->applyDashBoost(dashBoost);
        }
        for (auto &platform : m_platforms_top) {
            platform->applyDashBoost(dashBoost);
        }
        m_bg_background->applyDashBoost(dashBoost);
        m_bg_foreground->applyDashBoost(dashBoost);
        m_bg_midground->applyDashBoost(dashBoost);
        m_bg_sky->applyDashBoost(dashBoost);
    }
    m_clouds.erase(
    std::remove_if(
        m_clouds.begin(), m_clouds.end(),
        [this](const std::unique_ptr<Cloud>& cloud) -> bool {
            if (!cloud->update()) {
                return true;
            }
            return false;
        }
    ),
    m_clouds.end()
);
// Language: cpp
// Update lambda for bottom platforms
m_platforms_bottom.erase(
    std::remove_if(
        m_platforms_bottom.begin(), m_platforms_bottom.end(),
        [this](const std::unique_ptr<Platform>& platform) -> bool {
            if (!platform->update()) {
                m_obstacles.erase(platform.get());
                return true;
            }
            auto it = m_obstacles.find(platform.get());
            if (it != m_obstacles.end()) {
                it->second->update();
            }
            return false;
        }
    ),
    m_platforms_bottom.end()
);

m_platforms_top.erase(
    std::remove_if(
        m_platforms_top.begin(), m_platforms_top.end(),
        [this](const std::unique_ptr<Platform>& platform) -> bool {
            if (!platform->update()) {
                m_obstacles.erase(platform.get());
                return true;
            }
            auto it = m_obstacles.find(platform.get());
            if (it != m_obstacles.end()) {
                it->second->update();
            }
            return false;
        }
    ),
    m_platforms_top.end()
);
    m_bg_background->update();
    m_bg_foreground->update();
    m_bg_midground->update();
    m_bg_sky->update();
}

void GameScreen::render() {
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));

       m_bg_sky->draw(m_bg_sky->getX());
       m_bg_sky->draw(m_bg_sky->getWidth() * 2 + m_bg_sky->getX());


       m_bg_background->draw(m_bg_background->getX());
       m_bg_background->draw(m_bg_background->getWidth() * 2 + m_bg_background->getX());

       m_bg_midground->draw(m_bg_midground->getX());
       m_bg_midground->draw(m_bg_midground->getWidth() * 2 + m_bg_midground->getX());

       m_bg_foreground->draw(m_bg_foreground->getX());
       m_bg_foreground->draw(m_bg_foreground->getWidth() * 2 + m_bg_foreground->getX());


    for(auto &cloud : m_clouds) {
        cloud->draw();
    }

 // Language: cpp
// Render loop for platforms
for (auto &platform : m_platforms_bottom) {
    platform->draw();
    auto it = m_obstacles.find(platform.get());
    if (it != m_obstacles.end()) {
        it->second->draw();
    }
}
for (auto &platform : m_platforms_top) {
    platform->draw();
    auto it = m_obstacles.find(platform.get());
    if (it != m_obstacles.end()) {
        it->second->draw();
    }
}
for(auto &star : m_stars) {
    star->draw();
    }
    m_character->draw();
        if (config::snow && m_snow) {
        m_snow->draw();
    }
       if (config::fog) {
        Color fogColor = Fade(LIGHTGRAY, 0.4f);
        DrawRectangle(0, 0, config::SCREEN_WIDTH, config::SCREEN_HEIGHT, fogColor);
    }

    m_interface->draw(m_speed, m_stars_collected);

  if (!m_character->isAlive()) {
    const char *msg = "You died";
    int fontSize = 40;
    Color borderColor = BLACK;
    Color mainColor = RED;
    Vector2 pos = { config::SCREEN_WIDTH / 2 - 100, config::SCREEN_HEIGHT / 2 - 50 };

    // Draw border by drawing text with slight offsets
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            // Skip drawing the main text position
            if (dx == 0 && dy == 0) continue;
            DrawText(msg, pos.x + dx, pos.y + dy, fontSize, borderColor);
        }
    }
    // Draw the main text
    DrawText(msg, pos.x, pos.y, fontSize, mainColor);
}
    EndDrawing();
}