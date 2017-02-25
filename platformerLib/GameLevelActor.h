#pragma once
#include "ActorBase.h"
#include "PhysicalObject.h"
#include "Unit.h"

DECLARE_SMART(GameLevelActor, spGameLevelActor);
class GameLevelActor : public ActorBase
{
public:
   GameLevelActor(const PhysicalObject::Size& size);
   void AddAndExtend(const spActorBase& actor);
   void ScrollToShow(const PhysicalObject::Point& point);

   static const Distance& GetBuffer() { return kScrollBuffer; }
   static void SetBuffer(const Distance& buffer) { kScrollBuffer = buffer; }

private:
   void ExtendToInclude(const PhysicalObject& object);

   PhysicalObject::Size stage_size_;
   Distance distance_to_left_border_;

   static Distance kScrollBuffer;
};

