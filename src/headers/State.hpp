#ifndef STATE_HPP
#define STATE_HPP

class State {
public:
    virtual ~State() = default;

    virtual auto handleInput() -> void = 0;

    virtual auto update() -> void = 0;

    virtual auto render() -> void = 0;

    virtual auto getName() const -> const char * = 0;
};

#endif // STATE_HPP
