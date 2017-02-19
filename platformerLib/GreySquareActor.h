#pragma once

#include "ActorBase.h"

enum class Direction;

DECLARE_SMART(GreySquareActor, spGreySquareActor);
class GreySquareActor : public ActorBase
{
public:
   GreySquareActor(const PhysicalObject::Point& start_point);
   void Jump();
   void MoveHorizontally(Direction dir);
   void StopMoveHorizontally();

   virtual void doUpdate(const oxygine::UpdateState& us) override;

   static const Speed& GetMaxHorizontalSpeed() { return kMaxHorizontalSpeed; }
   static const Acceleration& GetMaxHorizontalMoveAcceleration() { return kHorizontalMoveAcceleration; }

private:
   void ApplyMoveSpeed(const oxygine::UpdateState& us);

private:
   static const PhysicalObject::SpeedVector kJumpSpeed;
   static const Speed kMaxHorizontalSpeed;
   static const Acceleration kHorizontalMoveAcceleration;

   Direction move_direction_;
};

