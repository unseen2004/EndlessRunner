#include "../headers/StarPopout.hpp"
#include "../headers/Constants.hpp"
#include "../headers/DebugLog.hpp"

StarPopout::StarPopout(Vector2 pos, const std::string &text, const Font &font)
    : m_position(pos), m_text(text), m_font(font), m_timer(0.0f),
      m_duration(constants::STAR_POPOUT_DURATION) {
    LOG("Created star popout at (" << pos.x << ", " << pos.y << "): " << text);
}

void StarPopout::update() {
    m_timer += GetFrameTime();
}

void StarPopout::draw() {
    float alpha = 1.0f - (m_timer / m_duration);
    if (alpha < 0.0f) alpha = 0.0f;
    Color color = Fade(YELLOW, alpha);
    int fontSize = m_font.baseSize;
    DrawTextEx(m_font, m_text.c_str(), m_position,
              static_cast<float>(fontSize), constants::STAR_POPOUT_SPACING, color);
}

bool StarPopout::isExpired() const {
    return (m_timer >= m_duration);
}