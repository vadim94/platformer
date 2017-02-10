#include "GroundActor.h"
#include "GameEngine.h"

GroundActor::GroundActor(const PhysicalObject::Point& startPoint)
{
	setColor(oxygine::Color::Green);
	SetLocation(startPoint);
	setSize(100, 5);
	GameEngine::getInstance().registrateGroundActor(this);
}

void GroundActor::doUpdate(const oxygine::UpdateState& us)
{
}

void GroundActor::SetLocation(const Point& location)
{
   setPosition(static_cast<float>(location.x.Value()), static_cast<float>(location.y.Value()));
}

PhysicalObject::Point GroundActor::GetLocation() const
{
   auto position = getPosition();
   return Point(pixel * position.x, pixel * position.y);
}