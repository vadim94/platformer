#include "GroundActor.h"
#include "GameEngine.h"

GroundActor::GroundActor(const PhysicalObject::Point& startPoint)
{
	setColor(oxygine::Color::Green);
	SetLocation(startPoint);
	setSize(100, 5);
	GameEngine::GetInstance().RegistrateObject(this);
}

void GroundActor::doUpdate(const oxygine::UpdateState& us)
{
}