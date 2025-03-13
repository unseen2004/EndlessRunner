#include "../headers/StarPopout.h"

StarPopout::StarPopout(Vector2 pos, const std::string &text)
    : m_position(pos), m_text(text), m_timer(0.0f), m_duration(1.0f) // duration in seconds
{}

void StarPopout::update() {
    float dt = GetFrameTime();
    m_timer += dt;
    m_position.y -= 20.0f * dt; // move upward
}

void StarPopout::draw() {
    float alpha = 1.0f - (m_timer / m_duration);
    Color color = Fade(YELLOW, alpha);
    int fontSize = 20;
    DrawText(m_text.c_str(), static_cast<int>(m_position.x), static_cast<int>(m_position.y), fontSize, color);
}

bool StarPopout::isExpired() const {
    return m_timer > m_duration;
}