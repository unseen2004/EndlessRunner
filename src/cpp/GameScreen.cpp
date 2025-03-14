#include "../headers/GameScreen.hpp"
#include "../headers/Constants.hpp"
#include "../headers/DebugLog.hpp"

bool GameScreen::s_invulnerability_active = false;
extern bool g_exitGame;

GameScreen::GameScreen(StateMachine &sm)
    : m_stateMachine(sm) {
    m_invulnerability_timer = constants::INVULNERABILITY_TIMER;
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
        m_character = std::make_unique<Character>(
            fs::path("resources/scarfy.png"),
            fs::path("resources/explosion.png"),
            fs::path("resources/sound/boom.wav"),
            m_speed
        );
        if (!m_character) throw std::runtime_error("Failed to load character");
        const char* textSample = "Some UTF-8 text";
        int codepointCount = 0;
        int *codepoints = LoadCodepoints(textSample, &codepointCount);
        m_replaySystem = std::make_unique<ReplaySystem>();
        font = LoadFontEx("resources/fonts/GenShinGothic-Regular.ttf",
                          constants::FONT_BASE_SIZE,
                          codepoints,
                          codepointCount);
        UnloadCodepoints(codepoints);
    } catch (const std::exception &e) {
        ERR("Error: " << e.what());
    }
    float platformX = constants::INITIAL_PLATFORM_X;
    float platformY = constants::INITIAL_PLATFORM_Y;
    m_platforms_bottom.push_back(std::make_unique<Platform>(m_speed, platformX, platformY, 1.0f));
    m_platforms_bottom.push_back(std::make_unique<Platform>(m_speed,
                                platformX + constants::PLATFORM_GAP,
                                platformY, 1.0f));
    m_startTime = std::chrono::steady_clock::now();
    if (config::snow) {
        m_snow = std::make_unique<Snow>(100, config::SCREEN_WIDTH, config::SCREEN_HEIGHT);
    }
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetTargetFPS(config::FRAMES);
}

GameScreen::~GameScreen() {
    if(!replay) {
        m_replaySystem->saveToFile("history.dat");
    }
    m_bg_background.reset();
    m_bg_foreground.reset();
    m_bg_midground.reset();
    m_bg_sky.reset();
    m_character.reset();
    m_interface.reset();
    UnloadFont(font);
    for (auto &cloud : m_clouds) {
        cloud.reset();
    }
    for (auto &platform : m_platforms_bottom) {
        platform.reset();
    }
    for (auto &platform : m_platforms_top) {
        platform.reset();
    }
    for (auto &star : m_stars) {
        star.reset();
    }
    m_snow.reset();
}

auto GameScreen::handleInput() -> void {
    if (IsKeyPressed(KEY_ENTER)) {
        if (!m_character->isAlive()) {
            m_stateMachine.changeState(std::make_unique<DeadScreen>(m_stateMachine));
        }
    }
    if (IsKeyPressed(KEY_E)) {
        g_exitGame = true;
    }
    m_input_jump = IsKeyPressed(KEY_SPACE);
    m_input_dash = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
    m_replaySystem->addInputFrame(m_input_jump, m_input_dash, GetFrameTime());
}

auto GameScreen::update() -> void {
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
    for (auto it = m_stars.begin(); it != m_stars.end();) {
        (*it)->update();
        if (CheckCollisionRecs(m_character->getCollisionRect(), (*it)->getBoundingBox())) {
            m_stars_collected++;
            Vector2 popPos{m_character->getCollisionRect().x, m_character->getCollisionRect().y};
            m_popouts.push_back(std::make_unique<StarPopout>(popPos, "Star!", font));
            it = m_stars.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = m_popouts.begin(); it != m_popouts.end();) {
        (*it)->update();
        if ((*it)->isExpired()) {
            it = m_popouts.erase(it);
        } else {
            ++it;
        }
    }
    float dt = GetFrameTime();
    float dashBoost = m_character->getDashBoost(dt);
    if (dashBoost > 0) {
        m_bg_background->applyDashBoost(dashBoost);
        m_bg_foreground->applyDashBoost(dashBoost);
        m_bg_midground->applyDashBoost(dashBoost);
        m_bg_sky->applyDashBoost(dashBoost);
        for (auto &cloud : m_clouds) {
            cloud->applyDashBoost(dashBoost);
        }
        for (auto &platform : m_platforms_bottom) {
            platform->applyDashBoost(dashBoost);
        }
        for (auto &platform : m_platforms_top) {
            platform->applyDashBoost(dashBoost);
        }
        for (auto &star : m_stars) {
            star->applyDashBoost(dashBoost);
        }
    }
    m_clouds.erase(std::remove_if(m_clouds.begin(), m_clouds.end(),
                  [this](const std::unique_ptr<Cloud> &cloud) {
                      return !cloud->update();
                  }),
                  m_clouds.end());
    m_platforms_bottom.erase(std::remove_if(m_platforms_bottom.begin(),
                           m_platforms_bottom.end(),
                           [this](const std::unique_ptr<Platform> &platform) {
                               return !platform->update();
                           }),
                           m_platforms_bottom.end());
    m_platforms_top.erase(std::remove_if(m_platforms_top.begin(),
                        m_platforms_top.end(),
                        [this](const std::unique_ptr<Platform> &platform) {
                            return !platform->update();
                        }),
                        m_platforms_top.end());
    m_bg_background->update();
    m_bg_foreground->update();
    m_bg_midground->update();
    m_bg_sky->update();
}

auto GameScreen::render() -> void {
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));

    m_bg_sky->draw(m_bg_sky->getX());
    m_bg_sky->draw(m_bg_sky->getWidth() * 2 + m_bg_sky->getX());
    m_bg_background->draw(m_bg_background->getX());
    m_bg_background->draw(m_bg_background->getWidth() * 2 + m_bg_background->getX());
    m_bg_midground->draw(m_bg_midground->getX());
    m_bg_midground->draw(m_bg_midground->getWidth() * 2 + m_bg_midground->getX());

    for (auto &platform : m_platforms_bottom) {
        platform->draw();
    }
    for (auto &platform : m_platforms_top) {
        platform->draw();
    }
    for (auto &star : m_stars) {
        star->draw();
    }

    m_character->draw();

    m_bg_foreground->draw(m_bg_foreground->getX());
    m_bg_foreground->draw(m_bg_foreground->getWidth() * 2 + m_bg_foreground->getX());

    for (auto &popout : m_popouts) {
        popout->draw();
    }

    if (config::fog) {
        Color fogColor = Fade(LIGHTGRAY, 0.4f);
        DrawRectangle(0, 0, config::SCREEN_WIDTH, config::SCREEN_HEIGHT, fogColor);
    }

    for (auto &cloud : m_clouds) {
        cloud->draw();
    }

    if (config::snow && m_snow) {
        m_snow->draw();
    }

    if (!m_character->isAlive()) {
        const char *msg = "You died";
        int fontSize = 40;
        Color borderColor = BLACK;
        Color mainColor = RED;
        Vector2 pos {static_cast<float>(config::SCREEN_WIDTH / 2 - 100),
                     static_cast<float>(config::SCREEN_HEIGHT / 2 - 50)};
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                if (dx == 0 && dy == 0) continue;
                DrawText(msg, pos.x + dx, pos.y + dy, fontSize, borderColor);
            }
        }
        DrawText(msg, pos.x, pos.y, fontSize, mainColor);
    }

    m_interface->draw(m_speed, m_stars_collected);

    EndDrawing();
}

auto GameScreen::handleDeathTransition() -> void {
    m_character->updateDeadAnimation();
    if (m_character->isDeadAnimationFinished()) {
        m_stateMachine.changeState(std::make_unique<DeadScreen>(m_stateMachine));
    }
}

auto GameScreen::isDeadAnimationFinished() -> bool {
    return !m_character->isAlive() && m_character->isDeadAnimationFinished();
}

auto GameScreen::spawnClouds() -> void {
    if (m_clouds.size() < config::MAX_CLOUDS) {
        int lastX = m_clouds.empty() ? 0 : m_clouds.back()->getX();
        if (m_clouds.empty() || lastX < config::SCREEN_WIDTH - config::PLATFORM_WIDTH) {
            try {
                int spawnY = Random::get(constants::CLOUD_MIN_Y, constants::CLOUD_MAX_Y);
                m_clouds.push_back(std::make_unique<Cloud>(
                    fs::path("resources/clouds/Cloud_" +
                             std::to_string(Random::get(constants::CLOUD_MIN_TYPE,
                                                         constants::CLOUD_MAX_TYPE)) +
                             ".png"),
                    m_speed,
                    Random::get(constants::CLOUD_MIN_SCALE, constants::CLOUD_MAX_SCALE),
                    config::SCREEN_WIDTH,
                    spawnY,
                    Random::get(constants::CLOUD_MIN_SPEED_FACTOR,
                                constants::CLOUD_MAX_SPEED_FACTOR)
                ));
            } catch (const std::exception &e) {
                ERR("Error: " << e.what());
            }
        }
    }
}

auto GameScreen::spawnPlatforms(std::vector<std::unique_ptr<Platform>> &platforms, bool bottom) -> void {
    if (platforms.size() < config::MAX_PLATFORMS) {
        int lastX = platforms.empty() ? 0 : platforms.back()->getX();
        if ((bottom && (platforms.empty() ||
             lastX < config::SCREEN_WIDTH - config::PLATFORM_WIDTH * constants::BOTTOM_PLATFORM_GAP_MULTIPLIER)) ||
            (!bottom && (platforms.empty() ||
             lastX < config::SCREEN_WIDTH - config::PLATFORM_WIDTH * constants::TOP_PLATFORM_GAP_MULTIPLIER))) {
            try {
                int spawnY = bottom
                    ? Random::get(constants::PLATFORM_BOTTOM_MIN,
                                  config::SCREEN_HEIGHT - constants::PLATFORM_BOTTOM_MAX_OFFSET)
                    : Random::get(0, constants::PLATFORM_TOP_MAX);
                auto newPlatform = std::make_unique<Platform>(m_speed,
                    config::SCREEN_WIDTH,
                    static_cast<float>(spawnY),
                    1.0f);
                platforms.push_back(std::move(newPlatform));
            } catch (const std::exception &e) {
                ERR("Error: " << e.what());
            }
        }
    }
}

auto GameScreen::spawnStars() -> void {
    if (m_stars.size() < config::MAX_STARS && GetRandomValue(0, 100) < 100) {
        float spawnX = static_cast<float>(config::SCREEN_WIDTH);
        float spawnWidth = constants::CLOUD_SPAWN_MARGIN;
        Rectangle spawnArea = {spawnX, 0, spawnWidth,
                               static_cast<float>(config::SCREEN_HEIGHT)};
        Star* newStar = Star::SpawnRandom(spawnArea, m_platforms_bottom);
        if (newStar) {
            m_stars.push_back(std::unique_ptr<Star>(newStar));
        }
    }
}

auto GameScreen::updateSpeedBasedOnTime(std::chrono::steady_clock::time_point start_time) -> void {
    auto currentTime = std::chrono::steady_clock::now();
    auto diff = currentTime - start_time;
    if (m_game_over) {
        m_speed = constants::SPEED_GAME_OVER;
    } else {
        m_speed = constants::BASE_SPEED +
                  config::e * std::chrono::duration_cast<std::chrono::seconds>(diff).count();
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
    }
    for (auto &platform : m_platforms_top) {
        platform->changeSpeed(m_speed);
    }
    for (auto &star : m_stars) {
        star->changeSpeed(m_speed);
    }
}