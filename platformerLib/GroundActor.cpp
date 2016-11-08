#include "GroundActor.h"
#include "GameEngine.h"

GroundActor::GroundActor(const PhysicalObject::Point& startPoint) : PhysicalObject{ startPoint }
{
	oxygine::ColorRectSprite::setColor(oxygine::Color::Green);
	oxygine::ColorRectSprite::setPosition(startPoint.x.Value(), startPoint.y.Value());
	oxygine::ColorRectSprite::setSize(100, 5);
	GameEngine::getInstance().registrateGroundActor(this);
}

void GroundActor::doUpdate(const oxygine::UpdateState& us)
{
}