#ifndef REPLAYSYSTEM_HPP
#define REPLAYSYSTEM_HPP

#include <vector>
#include <fstream>
#include <chrono>
#include <stdexcept>
#include <filesystem>
#include "raylib.h"

struct InputFrame {
    bool jumpPressed;
    bool dashPressed;
    float deltaTime;
};

struct GameSetupData {
    bool snow;
    bool fog;
    int randomSeed;
};

class ReplaySystem {
public:
    ReplaySystem();

    ~ReplaySystem();

    auto addInputFrame(bool jumpPressed, bool dashPressed, float deltaTime) -> void;

    auto saveToFile(const std::string &filename) -> void;

    auto loadFromFile(const std::string &filename) -> bool;

    auto startPlayback() -> void;

    auto advanceFrame() -> void;

    [[nodiscard]] auto isPlaybackFinished() const -> bool;

    [[nodiscard]] auto getCurrentInput() const -> const InputFrame &;

    auto getSetupData() -> GameSetupData & { return m_setupData; }
    [[nodiscard]] auto getSetupData() const -> const GameSetupData & { return m_setupData; }

private:
    std::vector<InputFrame> m_inputFrames;
    GameSetupData m_setupData;
    size_t m_currentFrameIndex;
    bool m_playbackActive;
};

#endif
