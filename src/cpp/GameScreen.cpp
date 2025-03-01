#include "../headers/GameScreen.h"


GameScreen::GameScreen(StateMachine& sm) : m_stateMachine(sm) {
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
                                                  fs::path("resources/boom.wav"),m_speed);
        if (!m_character) throw std::runtime_error("Failed to load character");

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        // Handle the error, e.g., by setting a flag or exiting the program
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
    m_character.reset();
}


void GameScreen::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        m_stateMachine.changeState(std::make_unique<DeadScreen>(m_stateMachine)); // Change to DeadScreen
    }
    if (IsKeyDown(KEY_SPACE)) {
        m_input_jump = true;
    } else {
        m_input_jump = false;
    }
}

void GameScreen::updateSpeedBasedOnTime( std::chrono::steady_clock::time_point start_time) {
    auto currentTime = std::chrono::steady_clock::now();
	auto diff = currentTime - start_time;


    if(!m_character->update(m_input_jump, m_input_dash)){
    	m_speed = 0.0f;
    }else{
    	m_speed = 1.0f + config::e * std::chrono::duration_cast<std::chrono::seconds>(diff).count();
   }
    m_bg_background->changeSpeed(m_speed);
    m_bg_foreground->changeSpeed(m_speed);
    m_bg_midground->changeSpeed(m_speed);
    m_bg_sky->changeSpeed(m_speed);
    m_character->changeSpeed(m_speed);

    for (auto &cloud: m_clouds) {
        cloud->changeSpeed(m_speed);
    }
    for (auto &platform: m_platforms_bottom) {
        platform->changeSpeed(m_speed);
        m_obstacles[platform.get()]->changeSpeed(m_speed);
    }
    for (auto &platform: m_platforms_top) {
        platform->changeSpeed(m_speed);
        m_obstacles[platform.get()]->changeSpeed(m_speed);
    }
    //std::cout << "Speed: " << m_speed << std::endl;//del
}

// za nisko, za gesto
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

void GameScreen::spawnPlatforms(std::vector<std::unique_ptr<Platform>>& platform, bool bottom) {

    if (platform.size() < config::MAX_PLATFORMS) {
        int lastX = platform.empty() ? 0 : platform.back()->getX();

        // Ensure the last platform is far enough before spawning a new one
        if (bottom && (platform.empty() || lastX < config::SCREEN_WIDTH - config::PLATFORM_WIDTH * 2) || !bottom && (platform.empty() || lastX < config::SCREEN_WIDTH - config::PLATFORM_WIDTH*4)) {
          try {
              int spawnY;
              if(bottom){
                	spawnY = Random::get(700, config::SCREEN_HEIGHT-300);
                }else{
                	 spawnY = Random::get(0, 100);
                }
                platform.push_back(std::make_unique<Platform>(m_speed, config::SCREEN_WIDTH, spawnY, 1.0f));
                if(Random::get(0,10) < 100){
	                    	m_obstacles[platform.back().get()] = std::make_unique<Obstacle>(*platform.back(), m_speed, Random::get(2, 4));
                }

            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
    if(bottom){
      //ovbst
      }
}


void GameScreen::update() {
    updateSpeedBasedOnTime(m_startTime);

    spawnClouds();
	spawnPlatforms(m_platforms_bottom, true);
	spawnPlatforms(m_platforms_top, false);





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

m_platforms_bottom.erase(
    std::remove_if(
        m_platforms_bottom.begin(), m_platforms_bottom.end(),
        [this](const std::unique_ptr<Platform>& platform) -> bool {
            if (!platform->update()) {
              m_obstacles.erase(platform.get());
              return true;
            }
            m_obstacles[platform.get()]->update();
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
            m_obstacles[platform.get()]->update();
            return false;
        }
    ),
    m_platforms_top.end()
);

        m_bg_background->update();
        m_bg_foreground->update();
        m_bg_midground->update();
        m_bg_sky->update();



		m_character->update(m_input_jump, m_input_dash);




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

       m_character->draw();

       DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f/GetFrameTime())), GetScreenWidth() - 220, 40, 20, GREEN); //del
		//std::cout<<m_speed<<"\n"; //del


               for (auto &cloud: m_clouds) {
            cloud->draw();
               }

           for (auto &platform: m_platforms_bottom) {
            platform->draw();
            m_obstacles[platform.get()]->draw();
               }

            for (auto &platform: m_platforms_top) {
            platform->draw();
            m_obstacles[platform.get()]->draw();
               }

       EndDrawing();
       /*
        for (auto &cloud: clouds) {
            cloud->draw();
        }
        */
}
