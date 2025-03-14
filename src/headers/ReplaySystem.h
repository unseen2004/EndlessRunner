// File: `src/headers/ReplaySystem.h`
#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>
#include "raylib.h"

// Store input state for each frame
struct InputFrame {
    bool jumpPressed;
    bool dashPressed;
    float deltaTime;   // Store time between frames for accurate replay
};

// Initial game setup data
struct GameSetupData {
    bool snow;
    bool fog;
    int randomSeed;    // Store random seed to recreate same level generation
};

class ReplaySystem {
public:
    ReplaySystem();
    ~ReplaySystem();

    // Record an input frame
    void addInputFrame(bool jumpPressed, bool dashPressed, float deltaTime);

    // Save and load functions
    void saveToFile(const std::string &filename);
    bool loadFromFile(const std::string &filename);

    // Playback control
    void startPlayback();
    void advanceFrame();
    bool isPlaybackFinished() const;

    // Get the current frame's input during replay
    const InputFrame& getCurrentInput() const;

    // Access the game setup data
    GameSetupData& getSetupData() { return m_setupData; }
    const GameSetupData& getSetupData() const { return m_setupData; }

private:
    std::vector<InputFrame> m_inputFrames;
    GameSetupData m_setupData;
    size_t m_currentFrameIndex;
    bool m_playbackActive;
};