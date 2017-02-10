#pragma once
#include "Event.h"

#include "GreySquareActor.h"

class MoveEvent : public oxygine::Event
{
public:
   enum { EVENT = eventID('M', 'O', 'V', 'E') };
   MoveEvent(GreySquareActor* movedObject, const PhysicalObject::Point& oldPosition,
      const PhysicalObject::Point& newPosition)
      : Event(EVENT), movedObject_(movedObject), oldPosition_(oldPosition), newPosition_(newPosition) {}

   GreySquareActor* movedObject_;
   PhysicalObject::Point oldPosition_;
   PhysicalObject::Point newPosition_;
};
