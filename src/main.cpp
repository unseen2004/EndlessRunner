#include "headers/includes.h"
#include "headers/config.h"
#include "headers/all_horizontal_movable.h"

namespace fs = std::filesystem;

class Character {
    Vector2 m_position;
    int m_currentFrame;
    int m_framesCounter;
    int m_framesSpeed;
    int m_jumps_left;
    bool m_is_jumping;
    int m_currentLine;
    Texture2D m_character;
    Texture2D m_explosion;
    Sound m_boom;
    fs::path m_pathCharacter;
    fs::path m_pathExplosion;
    fs::path m_pathSound;
    Rectangle m_frameRec;

public:
    Character(fs::path path1, fs::path path2, fs::path path3, float x = 300,
              float y = 800, int currentFrame = 0, int framesCounter = 0,
              int framesSpeed = 8, int currentLine = 0, bool is_jumping = false) : m_pathCharacter(path1),
        m_pathExplosion(path2),
        m_pathSound(path3), m_position{x, y},
        m_currentFrame(currentFrame),
        m_framesCounter(framesCounter), m_framesSpeed(framesSpeed),
        m_currentLine(0),
        m_jumps_left(config::JUMPS_NUMBER),
        m_is_jumping(is_jumping) {
        if (path1.empty() || path2.empty() || path3.empty()) {
            throw std::logic_error("File path cannot be empty");
        }
        m_character = LoadTexture(m_pathCharacter.string().c_str());
        m_explosion = LoadTexture(m_pathExplosion.string().c_str());
        m_boom = LoadSound(m_pathSound.string().c_str());
        m_frameRec = {0.0f, 0.0f, (float) m_character.width / 6, (float) m_character.height};
    }

    ~Character() {
        UnloadTexture(m_character);
        UnloadTexture(m_explosion);
        UnloadSound(m_boom);
    }

    void run() {
        ++m_framesCounter;
        if (m_framesCounter >= config::FRAMES / m_framesSpeed) {
            m_framesCounter = 0;
            ++m_currentFrame;
            if (m_currentFrame > 5) {
                m_currentFrame = 0;
            }
            m_frameRec.x = (float) m_currentFrame * (float) m_character.width / 6;
        }
        DrawTextureRec(m_character, m_frameRec, m_position, WHITE);
    }

    void dead() {
        InitAudioDevice();
        float frameWidth = (float) (m_explosion.width / NUM_FRAMES_PER_LINE);
        float frameHeight = (float) (m_explosion.height / NUM_LINES);

        m_currentFrame = 0;
        m_currentLine = 0;
        m_framesCounter = 0;

        Rectangle frameRec = {0, 0, frameWidth, frameHeight};
        m_position.x -= frameWidth / 2.0f;
        m_position.y -= frameHeight / 2.0f;
        bool active{true};
        PlaySound(m_boom);

        ++m_framesCounter;
        while (active) {
            if (m_framesCounter > 2) {
                ++m_currentFrame;

                if (m_currentFrame >= NUM_FRAMES_PER_LINE) {
                    m_currentFrame = 0;
                    ++m_currentLine;

                    if (m_currentLine >= NUM_LINES) {
                        m_currentLine = 0;
                        active = false;
                    }
                }

                m_framesCounter = 0;
            }

            frameRec.x = frameWidth * m_currentFrame;
            frameRec.y = frameHeight * m_currentLine;

            DrawTextureRec(m_explosion, frameRec, m_position, WHITE);
        }
    }

    bool init_jump() {
        if (m_jumps_left < 1) {
            return false;
        }
        --m_jumps_left;
    }
    // TO DO:
    // change y (increase->stop->decrease)
    // rolling movement
    void jump() {

    }

    void dash() {

    }

    void changeSpeed(int n) {
        m_framesSpeed += n;
        if (m_framesSpeed > MAX_FRAME_SPEED) m_framesSpeed = MAX_FRAME_SPEED;
        else if (m_framesSpeed < MIN_FRAME_SPEED) m_framesSpeed = MIN_FRAME_SPEED;
    }

    void newSpeed(int n) {
        m_framesSpeed = n;
        if (m_framesSpeed > MAX_FRAME_SPEED) m_framesSpeed = MAX_FRAME_SPEED;
        else if (m_framesSpeed < MIN_FRAME_SPEED) m_framesSpeed = MIN_FRAME_SPEED;
    }
};

class StateMachine {
};

class Interface {
};

class WelcomeScreen {
};

class DeathScreen {
};

class TableScreen {
};

class Game {
};

std::unique_ptr<Cloud> generateRandomCloud() {
    std::vector<std::filesystem::path> cloudPaths = {
        "../resources/clouds/Cloud_1.png",
        "../resources/clouds/Cloud_2.png",
        "../resources/clouds/Cloud_3.png"
    };

    int randomIndex = Random::get(0, 2);

    return std::make_unique<Cloud>(cloudPaths[randomIndex], 8.0f, config::SCREENWIDTH, 300.0f, 1.0f);
}

int main() {
    InitWindow(config::SCREENWIDTH, config::SCREENHEIGHT, "EndlessRunner");

    auto bg_background = std::make_unique<Background>(fs::path("../resources/background/BG.png"), 0.5f);
    auto bg_foreground = std::make_unique<Background>(fs::path("../resources/background/FG.png"));
    auto bg_midground = std::make_unique<Background>(fs::path("../resources/background/MG.png"), 0.5f);
    auto bg_sky = std::make_unique<Background>(fs::path("../resources/background/Sky.png"), 1.0f);

    Font japanese_font = LoadFont("../resources/fonts/NotoSansJP-Regular.ttf");
    Font emoji_font = LoadFont("../resources/fonts/noto_cjk.fnt");

    auto character = std::make_unique<Character>(fs::path("../resources/scarfy.png"),
                                                 fs::path("../resources/explosion.png"),
                                                 fs::path("../resources/boom.wav"));

    Obstacles *obstacleToDel = nullptr;
    std::vector<std::unique_ptr<Cloud> > clouds;

    SetTargetFPS(config::FRAMES);

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
                return -1;
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

        DrawTextEx(japanese_font, "おaa", (Vector2){300, 200}, japanese_font.baseSize, 2, RAYWHITE);

        EndDrawing();
    }

    UnloadFont(japanese_font);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

// 0,0
// width - 100, 0
// 0, height - 100
// width - 100, heigth - 100
//character: 300, w - 300
