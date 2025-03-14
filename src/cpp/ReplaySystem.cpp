// File: `src/cpp/ReplaySystem.cpp`
#include "../headers/ReplaySystem.h"
#include <stdexcept>

ReplaySystem::ReplaySystem()
    : m_currentFrameIndex(0), m_playbackActive(false) {
    // Default setup data
    m_setupData.snow = false;
    m_setupData.fog = false;
    m_setupData.randomSeed = GetRandomValue(0, 100000);
}

ReplaySystem::~ReplaySystem() { }

void ReplaySystem::addInputFrame(bool jumpPressed, bool dashPressed, float deltaTime) {
    InputFrame frame;
    frame.jumpPressed = jumpPressed;
    frame.dashPressed = dashPressed;
    frame.deltaTime = deltaTime;
    m_inputFrames.push_back(frame);
}

void ReplaySystem::saveToFile(const std::string &filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    // First write the setup data
    file.write(reinterpret_cast<const char*>(&m_setupData), sizeof(GameSetupData));

    // Write the number of frames
    size_t frameCount = m_inputFrames.size();
    file.write(reinterpret_cast<const char*>(&frameCount), sizeof(frameCount));

    // Write each frame
    for (const auto &frame : m_inputFrames) {
        file.write(reinterpret_cast<const char*>(&frame), sizeof(InputFrame));
    }

    file.close();

    // Generate a timestamp for the filename
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&time_t);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", localTime);

    // Get the final score and time
    int finalScore = 0;
    float finalTime = 0.0f;
    if (!m_inputFrames.empty()) {
        // Calculate total time
        for (const auto& frame : m_inputFrames) {
            finalTime += frame.deltaTime;
        }
    }

    // Rename the file to include metadata
    std::string newFilename = "replay_" + std::string(buffer) +
                              "_time" + std::to_string(static_cast<int>(finalTime)) +
                              ".dat";

    // Only rename if we used the default filename
    if (filename == "history.dat") {
        std::rename(filename.c_str(), newFilename.c_str());
    }
}

bool ReplaySystem::loadFromFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return false;
    }

    m_inputFrames.clear();

    // Read setup data
    file.read(reinterpret_cast<char*>(&m_setupData), sizeof(GameSetupData));

    // Read frame count
    size_t frameCount = 0;
    file.read(reinterpret_cast<char*>(&frameCount), sizeof(frameCount));

    // Read each frame
    for (size_t i = 0; i < frameCount; i++) {
        InputFrame frame;
        file.read(reinterpret_cast<char*>(&frame), sizeof(InputFrame));
        m_inputFrames.push_back(frame);
    }

    file.close();
    return true;
}

void ReplaySystem::startPlayback() {
    m_currentFrameIndex = 0;
    m_playbackActive = true;
}

void ReplaySystem::advanceFrame() {
    if (m_playbackActive && m_currentFrameIndex < m_inputFrames.size()) {
        m_currentFrameIndex++;
        if (m_currentFrameIndex >= m_inputFrames.size()) {
            m_playbackActive = false;
        }
    }
}

bool ReplaySystem::isPlaybackFinished() const {
    return !m_playbackActive;
}

const InputFrame& ReplaySystem::getCurrentInput() const {
    if (m_inputFrames.empty())
        throw std::runtime_error("No input frames loaded");

    if (m_currentFrameIndex < m_inputFrames.size())
        return m_inputFrames[m_currentFrameIndex];

    return m_inputFrames.back();
}