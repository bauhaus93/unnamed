#pragma once

enum class EventType {
    NONE,
    RENDER,
    UPDATE,
    QUIT,
    KEY_DOWN
};


class Event {

    EventType       type;

public:
                    Event();
    explicit        Event(EventType type_);
                    Event(const Event& other);
    virtual         ~Event() = default;

    EventType       GetType() const;
    void            SetType(EventType type_);

};
