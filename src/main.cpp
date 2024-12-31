#include "headers/includes.h"
#include "headers/config.h"
#include "headers/all_horizontal_movable.h"

namespace fs = std::filesystem;

class Character {
    Vector2 m_position;
    int m_currentFrame;
    int m_framesCounter;
    int m_framesSpeed;
    int m_currentLine;
    Texture2D m_character;
    Texture2D m_explosion;
    Sound m_boom;
    fs::path m_pathCharacter;
    fs::path m_pathExplosion;
    fs::path m_pathSound;
    Rectangle m_frameRec;

public:
    Character(fs::path path1, fs::path path2, fs::path path3, float x = 100.0f,
              float y = 200.0f, int currentFrame = 0, int framesCounter = 0,
              int framesSpeed = 8, int currentLine = 0) : m_pathCharacter(path1), m_pathExplosion(path2),
                                                          m_pathSound(path3), m_position{x, y},
                                                          m_currentFrame(currentFrame),
                                                          m_framesCounter(framesCounter), m_framesSpeed(framesSpeed),
                                                          m_currentLine(currentLine) {
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

    void jump() {}

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

int main() {
    InitWindow(config::SCREENWIDTH, config::SCREENHEIGHT, "EndlessRunner");
    bool tmp = false;

    Background bg_background("../resources/background/BG.png");
    Background bg_foreground("../resources/background/FG.png");
    Background bg_midground("../resources/background/MG.png");
    Background bg_sky("../resources/background/Sky.png");


    Character character("../resources/scarfy.png", "../resources/explosion.png", "../resources/boom.wav");

    SetTargetFPS(config::FRAMES);


    while (!WindowShouldClose()) {
        bg_background.changeX(-0.1f);
        bg_foreground.changeX(-1.0f);
        bg_midground.changeX(-0.5f);
        bg_sky.changeX(-1.0f);

        bg_background.resetIfOutsite();

        BeginDrawing();
        ClearBackground(GetColor(0x052c46ff));
        //ClearBackground(GetColor(0x052c46ff));


        bg_sky.draw(bg_sky.getX());
        bg_sky.draw(bg_sky.getWidth() * 2 + bg_sky.getX());

        bg_background.draw(bg_background.getX());
        bg_background.draw(bg_background.getWidth() * 2 + bg_background.getX());

        bg_midground.draw(bg_midground.getX());
        bg_midground.draw(bg_midground.getWidth() * 2 + bg_midground.getX());

        //------------------------------------------------------
        //                  Draw platforms

        //---------
        //draw character
        //ClearBackground(RAYWHITE);
        character.changeSpeed(1);
        character.run();
        /*
        if(!tmp) {
            tmp = true;
            character.dead();
        }
        */
        //------------------------------------------------------
        //bg_foreground.draw(bg_foreground.getX());
        //bg_foreground.draw(bg_foreground.getWidth() * 2 + bg_foreground.getX());


        DrawText("BACKGROUND SCROLLING & PARALLAX", 10, 10, 20, RED);
        DrawText("エンドレスランナーゲーム", config::SCREENWIDTH - 330, config::SCREENWIDTH - 20, 10, RAYWHITE);

        EndDrawing();
    }
    CloseAudioDevice();

    CloseWindow();

    return 0;
}
