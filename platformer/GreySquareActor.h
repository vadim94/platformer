#pragma once

#include "ColorRectSprite.h"
#include "PhysicalObject.h"

DECLARE_SMART(GreySquareActor, spGreySquareActor);
class GreySquareActor : public oxygine::ColorRectSprite, public PhysicalObject
{
public:
   GreySquareActor(const PhysicalObject::Point& startPoint);
   void Jump();

private:
   virtual void doUpdate(const oxygine::UpdateState& us) override;

private:
   static const PhysicalObject::SpeedVector jumpSpeed_;
};

