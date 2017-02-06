#pragma once

#include "Event.h"

class EndGameEvent : public oxygine::Event
{
public:
	enum { EVENT = eventID('E', 'N', 'D', 'G') };
	EndGameEvent() :Event(EVENT) {}
};