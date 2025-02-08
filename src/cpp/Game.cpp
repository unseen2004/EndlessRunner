#include "../headers/Game.h"
#include "../headers/WelcomeScreen.h"
#include "../headers/DeadScreen.h"
#include "../headers/TableScreen.h"
#include "../headers/Config.h"
#include "raylib.h"
#include <filesystem>

Game::Game() {
    init();
    loadResources();
}

void Game::init() {
    InitWindow(config::SCREENWIDTH, config::SCREENHEIGHT, "EndlessRunner");
    SetTargetFPS(config::FRAMES);

    stateMachine.addState("WelcomeScreen", std::make_unique<WelcomeScreen>(stateMachine));
    stateMachine.addState("GameScreen", std::make_unique<GameScreen>(stateMachine));
    stateMachine.addState("DeadScreen", std::make_unique<DeadScreen>(stateMachine));
    stateMachine.addState("TableScreen", std::make_unique<TableScreen>(stateMachine));

    stateMachine.changeState("WelcomeScreen");
}

std::unique_ptr<Cloud> generateRandomCloud() {
    std::vector<std::filesystem::path> cloudPaths = {
        "../resources/clouds/Cloud_1.png",
        "../resources/clouds/Cloud_2.png",
        "../resources/clouds/Cloud_3.png"
    };

    int randomIndex = Random::get(0, 2);

    return std::make_unique<Cloud>(cloudPaths[randomIndex], 8.0f, config::SCREENWIDTH, 300.0f, 1.0f);
}

void Game::loadResources() {
    bg_background = std::make_unique<Background>(std::filesystem::path("../resources/background/BG.png"), 0.5f);
    bg_foreground = std::make_unique<Background>(std::filesystem::path("../resources/background/FG.png"));
    bg_midground = std::make_unique<Background>(std::filesystem::path("../resources/background/MG.png"), 0.5f);
    bg_sky = std::make_unique<Background>(std::filesystem::path("../resources/background/Sky.png"), 1.0f);

    character = std::make_unique<Character>(std::filesystem::path("../resources/scarfy.png"),
                                            std::filesystem::path("../resources/explosion.png"),
                                            std::filesystem::path("../resources/boom.wav"));
}

void Game::unloadResources() {

    CloseAudioDevice();

    CloseWindow();
}
void Game::run() {
    while (!WindowShouldClose()) {
        bg_background->update();
        bg_foreground->update();
        bg_midground->update();
        bg_sky->update();

        // To DO: Add time restriction
        if (clouds.size() < config::MAX_CLOUDS && Random::get(1, 100) < 5) {
            // 2% chance to generate a cloud each frame
            clouds.push_back(generateRandomCloud());
        }
        for (auto &cloud: clouds) {
            cloud->update();
        }
        // Update clouds and remove those that are off-screen
        clouds.erase(std::remove_if(clouds.begin(), clouds.end(),
                                    [](const std::unique_ptr<Cloud> &cloud) { return !cloud->update(); }),
                     clouds.end());

        if (!obstacleToDel) {
            obstacleToDel = new Obstacles();
            if (obstacleToDel->getWidth() == 0) {
                std::cerr << "Failed to load platform texture" << std::endl;
                delete obstacleToDel;
                obstacleToDel = nullptr;
                return;
            }
        }

        BeginDrawing();
        ClearBackground(GetColor(0x052c46ff));

        bg_sky->draw(bg_sky->getX());
        bg_sky->draw(bg_sky->getWidth() * 2 + bg_sky->getX());

        bg_background->draw(bg_background->getX());
        bg_background->draw(bg_background->getWidth() * 2 + bg_background->getX());

        bg_midground->draw(bg_midground->getX());
        bg_midground->draw(bg_midground->getWidth() * 2 + bg_midground->getX());

        for (auto &cloud: clouds) {
            cloud->draw();
        }

        if (obstacleToDel->update()) {
            obstacleToDel->draw();
        } else {
            delete obstacleToDel;
            obstacleToDel = nullptr;
            std::cout << "deleted";
        }

        character->changeSpeed(1);
        character->run();

        DrawTextEx("おaa", (Vector2){300, 200}, 2, RAYWHITE);

        EndDrawing();
    }

    unloadResources();
}