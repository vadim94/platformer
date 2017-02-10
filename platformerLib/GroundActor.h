#pragma once

#include "ColorRectSprite.h"
#include "PhysicalObject.h"

DECLARE_SMART(GroundActor, spGroundActor);
class GroundActor : public oxygine::ColorRectSprite, public PhysicalObject
{
public:
	GroundActor(const PhysicalObject::Point& startPoint);
   virtual void SetLocation(const Point& location) override;
   virtual Point GetLocation() const override;
private:
	virtual void doUpdate(const oxygine::UpdateState& us) override;
};