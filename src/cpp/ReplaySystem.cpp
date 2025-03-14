#include "../headers/ReplaySystem.hpp"
#include "../headers/DebugLog.hpp"
#include "../headers/Constants.hpp"

namespace fs = std::filesystem;

ReplaySystem::ReplaySystem()
    : m_currentFrameIndex(0), m_playbackActive(false) {
    m_setupData.snow = false;
    m_setupData.fog = false;
    m_setupData.randomSeed = GetRandomValue(0, constants::RANDOM_SEED_MAX);
    LOG("ReplaySystem initialized");
}

ReplaySystem::~ReplaySystem() {
    LOG("ReplaySystem destroyed");
}

auto ReplaySystem::addInputFrame(bool jumpPressed, bool dashPressed, float deltaTime) -> void {
    m_inputFrames.push_back({jumpPressed, dashPressed, deltaTime});
}

auto ReplaySystem::saveToFile(const std::string &filename) -> void {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        ERR("Error opening file for writing: " << filename);
        return;
    }
    file.write(reinterpret_cast<const char*>(&m_setupData), sizeof(GameSetupData));
    size_t frameCount = m_inputFrames.size();
    file.write(reinterpret_cast<const char*>(&frameCount), sizeof(frameCount));
    for (auto const &frame : m_inputFrames) {
        file.write(reinterpret_cast<const char*>(&frame), sizeof(InputFrame));
    }
    file.close();
    auto now = std::chrono::system_clock::now();
    auto time_t_val = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&time_t_val);
    char buffer[constants::TIMESTAMP_BUFFER_SIZE];
    strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", localTime);
    float finalTime = 0.0f;
    for (auto const &frame : m_inputFrames) {
        finalTime += frame.deltaTime;
    }
    fs::path replayDir = fs::current_path() / "replays";
    if (!fs::exists(replayDir)) {
        fs::create_directories(replayDir);
    }
    auto newFilename = (replayDir / ("replay_" + std::string(buffer) +
                         "_time" + std::to_string(static_cast<int>(finalTime)) +
                         ".dat")).string();
    if (filename == constants::DEFAULT_REPLAY_FILENAME) {
        std::rename(filename.c_str(), newFilename.c_str());
        LOG("Replay saved as " << newFilename);
    }
}

auto ReplaySystem::loadFromFile(const std::string &filename) -> bool {
    fs::path fullPath = fs::current_path() / "replays" / filename;
    std::ifstream file(fullPath, std::ios::binary);
    if (!file.is_open()) {
        ERR("Error opening file for reading: " << fullPath);
        return false;
    }
    m_inputFrames.clear();
    file.read(reinterpret_cast<char*>(&m_setupData), sizeof(GameSetupData));
    size_t frameCount = 0;
    file.read(reinterpret_cast<char*>(&frameCount), sizeof(frameCount));
    for (size_t i = 0; i < frameCount; i++) {
        InputFrame frame;
        file.read(reinterpret_cast<char*>(&frame), sizeof(InputFrame));
        m_inputFrames.push_back(frame);
    }
    file.close();
    LOG("Loaded " << frameCount << " frames from replay file " << filename);
    return true;
}

auto ReplaySystem::startPlayback() -> void {
    m_currentFrameIndex = 0;
    m_playbackActive = true;
    LOG("Starting replay playback");
}

auto ReplaySystem::advanceFrame() -> void {
    if (m_playbackActive && m_currentFrameIndex < m_inputFrames.size()) {
        m_currentFrameIndex++;
        if (m_currentFrameIndex >= m_inputFrames.size()) {
            m_playbackActive = false;
            LOG("Replay playback finished");
        }
    }
}

auto ReplaySystem::isPlaybackFinished() const -> bool {
    return !m_playbackActive;
}

auto ReplaySystem::getCurrentInput() const -> const InputFrame & {
    if (m_inputFrames.empty()) {
        throw std::runtime_error("No input frames loaded");
    }
    if (m_currentFrameIndex < m_inputFrames.size()) {
        return m_inputFrames[m_currentFrameIndex];
    }
    return m_inputFrames.back();
}