// File: src/cpp/ReplayGameScreen.cpp
#include "../headers/ReplayGameScreen.hpp"
#include "../headers/ReplayScreen.hpp"
#include "../headers/DebugLog.hpp"
#include "../headers/Constants.hpp"

ReplayGameScreen::ReplayGameScreen(StateMachine &sm, const std::string &replayFile)
    : GameScreen(sm) // Call base class constructor
{
    LOG("Creating ReplayGameScreen with file: " << replayFile);
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
        ERR("Failed to load replay file: " << replayFile);
    }
}

ReplayGameScreen::~ReplayGameScreen() {
    LOG("Destructing ReplayGameScreen");
    // Don't save the replay when we're just playing one back
}

void ReplayGameScreen::handleInput() {
    // Only check for exit keys during replay
    if (IsKeyPressed(KEY_F)) {
        LOG("User pressed F - returning to replay selection");
        m_stateMachine.changeState(std::make_unique<ReplayScreen>(m_stateMachine));
    }
}

void ReplayGameScreen::update() {
    if (m_replaySystem->isPlaybackFinished() || m_replayFinished) {
        m_replayFinished = true;

        // Check if user wants to return to replay selection screen
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_F)) {
            LOG("Replay finished - user pressed key to return");
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
    DrawRectangle(constants::REPLAY_OVERLAY_X, constants::REPLAY_OVERLAY_Y,
                  constants::REPLAY_OVERLAY_WIDTH, constants::REPLAY_OVERLAY_HEIGHT,
                  Fade(BLACK, constants::REPLAY_OVERLAY_ALPHA));
    DrawText("REPLAY", constants::REPLAY_TEXT_X, constants::REPLAY_TEXT_Y,
             constants::REPLAY_TEXT_SIZE, RED);

    // Show "replay finished" message when complete
    if (m_replayFinished) {
        const char* msg = constants::REPLAY_FINISHED_MESSAGE;
        int textWidth = MeasureText(msg, constants::REPLAY_FINISHED_TEXT_SIZE);
        DrawRectangle(
            GetScreenWidth()/2 - textWidth/2 - constants::REPLAY_FINISHED_PADDING,
            GetScreenHeight()/2 - constants::REPLAY_FINISHED_HEIGHT/2,
            textWidth + constants::REPLAY_FINISHED_PADDING * 2,
            constants::REPLAY_FINISHED_HEIGHT,
            Fade(BLACK, constants::REPLAY_FINISHED_ALPHA)
        );
        DrawText(
            msg,
            GetScreenWidth()/2 - textWidth/2,
            GetScreenHeight()/2 - constants::REPLAY_FINISHED_TEXT_OFFSET,
            constants::REPLAY_FINISHED_TEXT_SIZE, WHITE
        );
    }
}