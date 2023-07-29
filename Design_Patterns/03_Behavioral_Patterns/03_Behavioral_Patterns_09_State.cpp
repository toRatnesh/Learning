/**********
    This example is implementation of State Dessign Pattern
****************/

#include <iostream>

class Switch;

class State {
    public:
        virtual ~State() = default;

        virtual void setOn(Switch * swtch)  = 0;
        virtual void setOff(Switch * swtch) = 0;
        virtual void display()              = 0;
        virtual void changeState(Switch * swtch, State & state);
};

class Switch {
    State * swtch_state;

    friend class State;
    void setState(State & state) {
        swtch_state = &state;
    }

    public:
    Switch();

    void on() {
        swtch_state->setOn(this);
    }
    void off() {
        swtch_state->setOff(this);
    }
    void currentState() {
        swtch_state->display();
    }    
};

class OnState : public State {
        OnState()   = default;
    public:
        virtual ~OnState()  = default;

        static OnState & instance();
        virtual void setOn(Switch * );
        virtual void setOff(Switch * swtch);
        virtual void display() { std::cout << "ON\n"; }
};

class OffState : public State {
        OffState()  = default;
    public:
        virtual ~OffState() = default;

        static OffState & instance();
        virtual void setOn(Switch * swtch);
        virtual void setOff(Switch * );
        virtual void display() { std::cout << "OFF\n"; }
};


void State::changeState(Switch * swtch, State & state) {
    swtch->setState(state);
}

OnState & OnState::instance() {
    static OnState on_state;
    return on_state;
}
void OnState::setOn(Switch * ) {
    std::cout << "Already in ON state\n";
}
void OnState::setOff(Switch * swtch) {
    std::cout << "Setting OFF from ON\n";
    //swtch->setState(OffState::instance());
    changeState(swtch, OffState::instance());
}

OffState & OffState::instance() {
    static OffState off_state;
    return off_state;
}
void OffState::setOn(Switch * swtch) {
    std::cout << "Setting ON from OFF\n";
    //swtch->setState(OnState::instance());
    changeState(swtch, OnState::instance());
}
void OffState::setOff(Switch * ) {
    std::cout << "Already in OFF state\n";
}

Switch::Switch() : swtch_state(&OffState::instance()) {}

int main() {
    Switch swtch;   swtch.currentState();
    swtch.on();     swtch.currentState();
    swtch.off();    swtch.currentState();
    swtch.off();    swtch.currentState();
    swtch.on();     swtch.currentState();
    swtch.on();     swtch.currentState();

	return 0;
}

/**********
    END OF FILE
****************/

