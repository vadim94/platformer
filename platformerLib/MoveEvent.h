#pragma once
#include "Event.h"

#include "GreySquareActor.h"

class MoveEvent : public oxygine::Event
{
public:
    enum { EVENT = eventID('M', 'O', 'V', 'E') };
    MoveEvent(GreySquareActor* moved_object, const PhysicalObject::Point& old_position,
        const PhysicalObject::Point& new_position)
        : Event(EVENT), moved_object_(moved_object), old_position_(old_position), new_position_(new_position) {}

    GreySquareActor* moved_object_;
    PhysicalObject::Point old_position_;
    PhysicalObject::Point new_position_;
};
