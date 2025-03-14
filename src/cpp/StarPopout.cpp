#include "../headers/StarPopout.hpp"
#include "../headers/Constants.hpp"
#include "../headers/DebugLog.hpp"

StarPopout::StarPopout(Vector2 pos, const std::string &text, const Font &font) :
    m_position(pos), m_text(text), m_font(font), m_timer(0.0f), m_duration(constants::STAR_POPOUT_DURATION) {}

auto StarPopout::update() -> void { m_timer += GetFrameTime(); }

auto StarPopout::draw() -> void {
    float alpha = 1.0f - (m_timer / m_duration);
    if (alpha < 0.0f)
        alpha = 0.0f;
    Color color = Fade(YELLOW, alpha);
    DrawTextEx(m_font, m_text.c_str(), m_position, static_cast<float>(m_font.baseSize), constants::STAR_POPOUT_SPACING,
               color);
}

auto StarPopout::isExpired() const -> bool { return (m_timer >= m_duration); }
