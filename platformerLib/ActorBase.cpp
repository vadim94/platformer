#include "ActorBase.h"

void ActorBase::SetLocation(const Point& location)
{
   setPosition(static_cast<float>(location.x.Value()), static_cast<float>(location.y.Value()));
}
PhysicalObject::Point ActorBase::GetLocation() const
{
   auto position = getPosition();
   return Point(pixel * position.x, pixel * position.y);
}

PhysicalObject::Size ActorBase::GetSize() const
{
   auto size = getSize();
   return{ size.x * pixel, size.y * pixel };
}
void ActorBase::SetSize(const Size& size)
{
   setSize(static_cast<float>(size.x.Value()), static_cast<float>(size.y.Value()));
}
