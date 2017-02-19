#include "ActorBase.h"

void ActorBase::SetLocation(const Point& location)
{
   setPosition(static_cast<float>(location.x.Value()), static_cast<float>(location.y.Value()));
}
PhysicalObject::Point ActorBase::GetLocation() const
{
   auto position = getPosition();
   return Point(kPixel * position.x, kPixel * position.y);
}

PhysicalObject::Size ActorBase::GetSize() const
{
   auto size = getSize();
   return{ size.x * kPixel, size.y * kPixel };
}
void ActorBase::SetSize(const Size& size)
{
   setSize(static_cast<float>(size.x.Value()), static_cast<float>(size.y.Value()));
}
