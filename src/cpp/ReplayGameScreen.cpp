// File: src/cpp/ReplayGameScreen.cpp
#include "../headers/ReplayGameScreen.h"
#include "../headers/ReplayScreen.h"

ReplayGameScreen::ReplayGameScreen(StateMachine &sm, const std::string &replayFile)
    : GameScreen(sm) // Call base class constructor
{
    std::cout<<"in replaygamescreen"<<std::endl;
    replay = true;
    m_replaySystem = std::make_unique<ReplaySystem>();

    // Load the replay file
    if (m_replaySystem->loadFromFile(replayFile)) {
        // Initialize the random seed to ensure the same level generation
        SetRandomSeed(m_replaySystem->getSetupData().randomSeed);
        m_replaySystem->startPlayback();
    } else {
        // Handle loading error
        m_replayFinished = true;
    }
}

ReplayGameScreen::~ReplayGameScreen() {
    std::cout<<"Destructing ReplayGameScreen"<<std::endl;
    // Don't save the replay when we're just playing one back
}

void ReplayGameScreen::handleInput() {
    // Only check for exit keys during replay
    if (IsKeyPressed(KEY_F)) {
        m_stateMachine.changeState(std::make_unique<ReplayScreen>(m_stateMachine));
    }
}

void ReplayGameScreen::update() {
    if (m_replaySystem->isPlaybackFinished() || m_replayFinished) {
        m_replayFinished = true;

        // Check if user wants to return to replay selection screen
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_F)) {
            m_stateMachine.changeState(std::make_unique<ReplayScreen>(m_stateMachine));
        }
        return;
    }

    // Get the current input from the replay system
    const InputFrame& input = m_replaySystem->getCurrentInput();

    // Override input variables with recorded ones
    m_input_jump = input.jumpPressed;
    m_input_dash = input.dashPressed;

    // Use base class update logic with our injected inputs
    GameScreen::update();

    // Advance to next frame in replay
    m_replaySystem->advanceFrame();
}

void ReplayGameScreen::render() {
    // Use the base class render method first
    GameScreen::render();

    // Add an overlay indicating this is a replay
    DrawRectangle(10, 10, 120, 30, Fade(BLACK, 0.7f));
    DrawText("REPLAY", 15, 15, 20, RED);

    // Show "replay finished" message when complete
    if (m_replayFinished) {
        const char* msg = "Replay Finished - Press SPACE to return";
        int textWidth = MeasureText(msg, 30);
        DrawRectangle(
            GetScreenWidth()/2 - textWidth/2 - 10,
            GetScreenHeight()/2 - 20,
            textWidth + 20, 40,
            Fade(BLACK, 0.7f)
        );
        DrawText(
            msg,
            GetScreenWidth()/2 - textWidth/2,
            GetScreenHeight()/2 - 15,
            30, WHITE
        );
    }
}