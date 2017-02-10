#include "GreySquareActor.h"
#include "GameEngine.h"
#include "Direction.h"
#include "MoveEvent.h"
#include "Stage.h"

const PhysicalObject::SpeedVector GreySquareActor::jumpSpeed_{ pixelPerSecond * 0, pixelPerSecond * -400 };
const Speed GreySquareActor::maxHorizontalSpeed_{ pixelPerSecond * 500 };
const Acceleration GreySquareActor::horizontalMoveAcceleration_{ pixelPerSquareSecond * 2000 };

namespace
{
   Time getTime(const oxygine::UpdateState& us)
   {
      return us.dt / 1000.0 * second;
   }
}

GreySquareActor::GreySquareActor(const PhysicalObject::Point& startPoint) : moveDirection_{ Direction::NotChanged }
{
   setColor(oxygine::Color::Silver);
   SetLocation(startPoint);
   setSize(100, 100);
}

void GreySquareActor::doUpdate(const oxygine::UpdateState& us)
{
   applyMoveSpeed(us);
   Point oldLocation = GetLocation();
   CalculateNewLocation(us);
   Point projectedLocation = GetLocation();

   MoveEvent event{this, oldLocation, projectedLocation };
   if (oxygine::Stage::instance) // Is null during tests.
   {
      oxygine::Stage::instance->dispatchEvent(&event);
   }
}

void GreySquareActor::applyMoveSpeed(const oxygine::UpdateState& us)
{
   auto speed = GetSpeed();
   const auto speedDif = getTime(us) * horizontalMoveAcceleration_.Abs();

   if(moveDirection_ == Direction::Right)
   {
      speed.x = std::min(maxHorizontalSpeed_.Abs(), (speed.x + speedDif));
   }
   else if (moveDirection_ == Direction::Right || moveDirection_ == Direction::Left)
   {
      speed.x = std::max(-(maxHorizontalSpeed_.Abs()), (speed.x - speedDif));
   }
   else if (moveDirection_ == Direction::NotChanged)
   {
      const int sign = speed.x.Value() >= 0 ? 1 : -1;
      auto newModuleOfSpeed = std::max((speed.x.Abs() - speedDif.Abs()), 0 * pixelPerSecond);
      speed.x = sign * newModuleOfSpeed;
   }

   SetSpeed(speed);
}

void GreySquareActor::Jump()
{
   auto speed = GetSpeed();
   if(speed.y > 0 * pixelPerSecond) speed.y *= 0;
   SetSpeed(speed + jumpSpeed_);
}

void GreySquareActor::MoveHorizontally(Direction dir)
{
   if (dir == Direction::NotChanged || dir == Direction::Up || dir == Direction::Down)
      throw std::logic_error("can move only horizontally");

   moveDirection_ = dir;
}

void GreySquareActor::StopMoveHorizontally()
{
   moveDirection_ = Direction::NotChanged;
}

void GreySquareActor::SetLocation(const Point& location)
{
   setPosition(static_cast<float>(location.x.Value()), static_cast<float>(location.y.Value()));
}
PhysicalObject::Point GreySquareActor::GetLocation() const
{
   auto position = getPosition();
   return Point(pixel * position.x, pixel * position.y);
}