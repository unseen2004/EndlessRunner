#include "../headers/ReplaySystem.hpp"
#include "../headers/DebugLog.hpp"
#include "../headers/Constants.hpp"

namespace fs = std::filesystem;

ReplaySystem::ReplaySystem()
    : m_currentFrameIndex(0), m_playbackActive(false) {
    // Default setup data
    m_setupData.snow = false;
    m_setupData.fog = false;
    m_setupData.randomSeed = GetRandomValue(0, constants::RANDOM_SEED_MAX);
    LOG("ReplaySystem initialized");
}

ReplaySystem::~ReplaySystem() {
    LOG("ReplaySystem destroyed");
}

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
        ERR("Error opening file for writing: " << filename);
        return;
    }

    // Write the setup data
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
    auto time_t_val = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&time_t_val);
    char buffer[constants::TIMESTAMP_BUFFER_SIZE];
    strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", localTime);

    // Calculate final time
    float finalTime = 0.0f;
    for (const auto& frame : m_inputFrames) {
        finalTime += frame.deltaTime;
    }

    // Create the "replays" directory if it doesn't exist
    fs::path replayDir = fs::current_path() / "replays";
    if (!fs::exists(replayDir)) {
        fs::create_directories(replayDir);
    }

    // Compose the new filename inside the "replays" directory
    std::string newFilename = (replayDir / ("replay_" + std::string(buffer) +
                              "_time" + std::to_string(static_cast<int>(finalTime)) +
                              ".dat")).string();

    // Rename the file if using the default filename
    if (filename == constants::DEFAULT_REPLAY_FILENAME) {
        std::rename(filename.c_str(), newFilename.c_str());
        LOG("Replay saved as " << newFilename);
    }
}

bool ReplaySystem::loadFromFile(const std::string &filename) {
    // Create full path: current directory / replays / filename
    fs::path fullPath = fs::current_path() / "replays" / filename;
    std::ifstream file(fullPath, std::ios::binary);
    if (!file.is_open()) {
        ERR("Error opening file for reading: " << fullPath);
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
    LOG("Loaded " << frameCount << " frames from replay file " << filename);
    return true;
}

void ReplaySystem::startPlayback() {
    m_currentFrameIndex = 0;
    m_playbackActive = true;
    LOG("Starting replay playback");
}

void ReplaySystem::advanceFrame() {
    if (m_playbackActive && m_currentFrameIndex < m_inputFrames.size()) {
        m_currentFrameIndex++;
        if (m_currentFrameIndex >= m_inputFrames.size()) {
            m_playbackActive = false;
            LOG("Replay playback finished");
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