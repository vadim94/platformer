#include "EnvironmentScroller.h"

void EnvironmentScroller::Add(PhysicalObject* object)
{
   environmentObjects_.push_back(object);
}

void EnvironmentScroller::MoveBy(const Distance& distance)
{
   const PhysicalObject::Point transition{ distance, pixel * 0 };
   for (auto object : environmentObjects_)
   {
      object->SetLocation(object->GetLocation() + transition);
   }
}

