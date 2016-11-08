#pragma once

#include "ColorRectSprite.h"
#include "PhysicalObject.h"

enum class Direction;

DECLARE_SMART(GreySquareActor, spGreySquareActor);
class GreySquareActor : public oxygine::ColorRectSprite, public PhysicalObject
{
public:
   GreySquareActor(const PhysicalObject::Point& startPoint);
   void Jump();
   void MoveHorizontally(Direction dir);
   void StopMoveHorizontally();

   virtual void doUpdate(const oxygine::UpdateState& us) override;

   static const Speed& GetMaxHorizontalSpeed() { return maxHorizontalSpeed_; }
   static const Acceleration& GetMaxHorizontalMoveAcceleration() { return horizontalMoveAcceleration_; }

private:
   void applyMoveSpeed(const oxygine::UpdateState& us);

private:
   static const PhysicalObject::SpeedVector jumpSpeed_;
   static const Speed maxHorizontalSpeed_;
   static const Acceleration horizontalMoveAcceleration_;

   Direction moveDirection_;
};

