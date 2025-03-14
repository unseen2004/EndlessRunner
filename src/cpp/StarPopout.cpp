#include "../headers/StarPopout.hpp"

StarPopout::StarPopout(Vector2 pos, const std::string &text, const Font &font)
    : m_position(pos), m_text(text), m_font(font), m_timer(0.0f), m_duration(3.0f) {
}

void StarPopout::update() {
    m_timer += GetFrameTime();
}

void StarPopout::draw() {
    float alpha = 1.0f - (m_timer / m_duration);
    if (alpha < 0.0f) alpha = 0.0f;
    Color color = Fade(YELLOW, alpha);
    int fontSize = m_font.baseSize;  // Adjust if needed
    DrawTextEx(m_font, m_text.c_str(), m_position, (float)fontSize, 2.0f, color);
}

bool StarPopout::isExpired() const {
    return (m_timer >= m_duration);
}