#include "../headers/ReplayGameScreen.hpp"
#include "../headers/Constants.hpp"
#include "../headers/DebugLog.hpp"
#include "../headers/ReplayScreen.hpp"

ReplayGameScreen::ReplayGameScreen(StateMachine &sm, const std::string &replayFile) : GameScreen(sm) {
    LOG("Creating ReplayGameScreen with file: " << replayFile);
    replay = true;
    m_replaySystem = std::make_unique<ReplaySystem>();
    if (m_replaySystem->loadFromFile(replayFile)) {
        SetRandomSeed(m_replaySystem->getSetupData().randomSeed);
        m_replaySystem->startPlayback();
    }
    else {
        m_replayFinished = true;
        ERR("Failed to load replay file: " << replayFile);
    }
}

ReplayGameScreen::~ReplayGameScreen() { LOG("Destructing ReplayGameScreen"); }

auto ReplayGameScreen::handleInput() -> void {
    if (IsKeyPressed(KEY_F)) {
        LOG("User pressed F - returning to replay selection");
        m_stateMachine.changeState(std::make_unique<ReplayScreen>(m_stateMachine));
    }
}

auto ReplayGameScreen::update() -> void {
    if (m_replaySystem->isPlaybackFinished() || m_replayFinished) {
        m_replayFinished = true;
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_F)) {
            LOG("Replay finished - user pressed key to return");
            m_stateMachine.changeState(std::make_unique<ReplayScreen>(m_stateMachine));
        }
        return;
    }
    const InputFrame &input = m_replaySystem->getCurrentInput();
    m_input_jump = input.jumpPressed;
    m_input_dash = input.dashPressed;
    GameScreen::update();
    m_replaySystem->advanceFrame();
}

auto ReplayGameScreen::render() -> void {
    GameScreen::render();
    DrawRectangle(constants::REPLAY_OVERLAY_X, constants::REPLAY_OVERLAY_Y, constants::REPLAY_OVERLAY_WIDTH,
                  constants::REPLAY_OVERLAY_HEIGHT, Fade(BLACK, constants::REPLAY_OVERLAY_ALPHA));
    DrawText("REPLAY", constants::REPLAY_TEXT_X, constants::REPLAY_TEXT_Y, constants::REPLAY_TEXT_SIZE, RED);
    if (m_replayFinished) {
        const char *msg = constants::REPLAY_FINISHED_MESSAGE;
        int textWidth = MeasureText(msg, constants::REPLAY_FINISHED_TEXT_SIZE);
        DrawRectangle(GetScreenWidth() / 2 - textWidth / 2 - constants::REPLAY_FINISHED_PADDING,
                      GetScreenHeight() / 2 - constants::REPLAY_FINISHED_HEIGHT / 2,
                      textWidth + constants::REPLAY_FINISHED_PADDING * 2, constants::REPLAY_FINISHED_HEIGHT,
                      Fade(BLACK, constants::REPLAY_FINISHED_ALPHA));
        DrawText(msg, GetScreenWidth() / 2 - textWidth / 2,
                 GetScreenHeight() / 2 - constants::REPLAY_FINISHED_TEXT_OFFSET, constants::REPLAY_FINISHED_TEXT_SIZE,
                 WHITE);
    }
}
