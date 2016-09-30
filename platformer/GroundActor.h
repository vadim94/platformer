#pragma once

#include "ColorRectSprite.h"
#include "PhysicalObject.h"

DECLARE_SMART(GroundActor, spGroundActor);
class GroundActor : public oxygine::ColorRectSprite, public PhysicalObject
{
public:
	GroundActor(const PhysicalObject::Point& startPoint);

private:
	virtual void doUpdate(const oxygine::UpdateState& us) override;
};