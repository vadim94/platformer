#include "GreySquareActor.h"

const PhysicalObject::SpeedVector GreySquareActor::jumpSpeed_{ Speed(0), Speed(-400) };

GreySquareActor::GreySquareActor(const PhysicalObject::Point& startPoint) : PhysicalObject{ startPoint }
{
   setColor(oxygine::Color::Silver);
   setPosition(startPoint.x.Value(), startPoint.y.Value());
   setSize(100, 100);
}

void GreySquareActor::doUpdate(const oxygine::UpdateState& us)
{
   Update(us);
   setPosition(GetLocation().x.Value(), GetLocation().y.Value());
}

void GreySquareActor::Jump()
{
   auto speed = GetSpeed();
   if(speed.y.Value() > 0) speed.y *= 0;
   SetSpeed(speed + jumpSpeed_);
}