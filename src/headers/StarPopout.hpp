#ifndef STARPOPOUT_HPP
#define STARPOPOUT_HPP

#include <string>
#include "raylib.h"

class StarPopout {
public:
    StarPopout(Vector2 pos, const std::string &text, const Font &font);

    auto update() -> void;

    auto draw() -> void;

    auto isExpired() const -> bool;

private:
    Vector2 m_position;
    std::string m_text;
    float m_timer;
    float m_duration;
    Font m_font;
};

#endif // STARPOPOUT_HPP
