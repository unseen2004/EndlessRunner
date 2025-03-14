// File: `src/headers/ReplaySystem.h`
// Language: cpp
#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include "raylib.h"

// ReplayFrame contains the game state at one frame.
struct ReplayFrame {
    Vector2 characterPosition;
    float characterRotation;
    std::vector<Vector2> platformPositions;
    std::vector<Vector2> cloudPositions;
    float gameSpeed;
    int starsCollected;
    float gameTime;
};

class ReplaySystem {
public:
    ReplaySystem();
    ~ReplaySystem();

    // Record a replay frame.
    void addFrame(const ReplayFrame &frame);
    // Save recorded frames to a binary file.
    void saveToFile(const std::string &filename);
    // Load recorded frames from a binary file.
    bool loadFromFile(const std::string &filename);
    // Begin replay playback.
    void startPlayback();
    // Advance to next frame.
    void advanceFrame();
    // Returns if replay playback is finished.
    bool isPlaybackFinished() const;
    // Returns the current frame.
    const ReplayFrame & getCurrentFrame() const;

private:
    std::vector<ReplayFrame> m_frames;
    size_t m_currentFrameIndex = 0;
    bool m_playbackActive = false;
};;;