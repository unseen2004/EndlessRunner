#ifndef REPLAYSYSTEM_HPP
#define REPLAYSYSTEM_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>
#include <stdexcept>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cstdio>
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

    void addInputFrame(bool jumpPressed, bool dashPressed, float deltaTime);

    void saveToFile(const std::string &filename);

    bool loadFromFile(const std::string &filename);

    void startPlayback();

    void advanceFrame();

    bool isPlaybackFinished() const;

    const InputFrame &getCurrentInput() const;

    GameSetupData &getSetupData() { return m_setupData; }
    const GameSetupData &getSetupData() const { return m_setupData; }

private:
    std::vector<InputFrame> m_inputFrames;
    GameSetupData m_setupData;
    size_t m_currentFrameIndex;
    bool m_playbackActive;
};

#endif // REPLAYSYSTEM_HPP
