#pragma once

enum class EventType {
    NONE,
    RENDER,
    UPDATE,
    QUIT
};


class Event {

    EventType       type;

public:
                    Event();
    explicit        Event(EventType type_);
                    Event(const Event& other);

    EventType       GetType() const;
    void            SetType(EventType type_);

};
