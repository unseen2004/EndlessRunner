// File: `src/cpp/ReplaySystem.cpp`
// Language: cpp
#include "../headers/ReplaySystem.h"
#include <stdexcept>

ReplaySystem::ReplaySystem() : m_currentFrameIndex(0), m_playbackActive(false) { }

ReplaySystem::~ReplaySystem() { }

void ReplaySystem::addFrame(const ReplayFrame &frame) {
    m_frames.push_back(frame);
}

void ReplaySystem::saveToFile(const std::string &filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    size_t frameCount = m_frames.size();
    file.write(reinterpret_cast<const char*>(&frameCount), sizeof(frameCount));
    for (const auto &frame : m_frames) {
        file.write(reinterpret_cast<const char*>(&frame.characterPosition), sizeof(Vector2));
        file.write(reinterpret_cast<const char*>(&frame.characterRotation), sizeof(float));

        size_t numPlatforms = frame.platformPositions.size();
        file.write(reinterpret_cast<const char*>(&numPlatforms), sizeof(size_t));
        for (const auto &pos : frame.platformPositions) {
            file.write(reinterpret_cast<const char*>(&pos), sizeof(Vector2));
        }

        size_t numClouds = frame.cloudPositions.size();
        file.write(reinterpret_cast<const char*>(&numClouds), sizeof(size_t));
        for (const auto &pos : frame.cloudPositions) {
            file.write(reinterpret_cast<const char*>(&pos), sizeof(Vector2));
        }

        file.write(reinterpret_cast<const char*>(&frame.gameSpeed), sizeof(float));
        file.write(reinterpret_cast<const char*>(&frame.starsCollected), sizeof(int));
        file.write(reinterpret_cast<const char*>(&frame.gameTime), sizeof(float));
    }
    file.close();
}

bool ReplaySystem::loadFromFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return false;
    }
    m_frames.clear();
    size_t frameCount = 0;
    file.read(reinterpret_cast<char*>(&frameCount), sizeof(frameCount));
    for (size_t i = 0; i < frameCount; i++) {
        ReplayFrame frame;
        file.read(reinterpret_cast<char*>(&frame.characterPosition), sizeof(Vector2));
        file.read(reinterpret_cast<char*>(&frame.characterRotation), sizeof(float));

        size_t numPlatforms = 0;
        file.read(reinterpret_cast<char*>(&numPlatforms), sizeof(size_t));
        for (size_t j = 0; j < numPlatforms; j++) {
            Vector2 pos;
            file.read(reinterpret_cast<char*>(&pos), sizeof(Vector2));
            frame.platformPositions.push_back(pos);
        }

        size_t numClouds = 0;
        file.read(reinterpret_cast<char*>(&numClouds), sizeof(size_t));
        for (size_t j = 0; j < numClouds; j++) {
            Vector2 pos;
            file.read(reinterpret_cast<char*>(&pos), sizeof(Vector2));
            frame.cloudPositions.push_back(pos);
        }
        file.read(reinterpret_cast<char*>(&frame.gameSpeed), sizeof(float));
        file.read(reinterpret_cast<char*>(&frame.starsCollected), sizeof(int));
        file.read(reinterpret_cast<char*>(&frame.gameTime), sizeof(float));
        m_frames.push_back(frame);
    }
    file.close();
    return true;
}

void ReplaySystem::startPlayback() {
    m_currentFrameIndex = 0;
    m_playbackActive = true;
}

void ReplaySystem::advanceFrame() {
    if (m_playbackActive && m_currentFrameIndex < m_frames.size()) {
        m_currentFrameIndex++;
        if (m_currentFrameIndex >= m_frames.size()) {
            m_playbackActive = false;
        }
    }
}

bool ReplaySystem::isPlaybackFinished() const {
    return !m_playbackActive;
}

const ReplayFrame & ReplaySystem::getCurrentFrame() const {
    if (m_frames.empty())
        throw std::runtime_error("No frames loaded");
    if (m_currentFrameIndex < m_frames.size())
        return m_frames[m_currentFrameIndex];
    return m_frames.back();
}