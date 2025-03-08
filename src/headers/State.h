#ifndef STATE_H
#define STATE_H

class State {
public:
    virtual ~State() = default;

    virtual void handleInput() = 0;

    virtual void update() = 0;

    virtual void render() = 0;

    virtual const char *getName() const = 0;
};

#endif // STATE_H
