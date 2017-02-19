#include "EnvironmentScroller.h"

void EnvironmentScroller::Add(PhysicalObject* object)
{
   environment_objects_.push_back(object);
}

void EnvironmentScroller::MoveBy(const Distance& distance)
{
   const PhysicalObject::Point transition{ distance, kPixel * 0 };
   for (auto object : environment_objects_)
   {
      object->SetLocation(object->GetLocation() + transition);
   }
}

