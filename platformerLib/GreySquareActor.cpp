#include "GreySquareActor.h"
#include "GameEngine.h"
#include "Direction.h"

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

GreySquareActor::GreySquareActor(const PhysicalObject::Point& startPoint)
   : PhysicalObject{ startPoint }
   , moveDirection_{ Direction::NotChanged }
{
   setColor(oxygine::Color::Silver);
   setPosition(startPoint.x.Value(), startPoint.y.Value());
   setSize(100, 100);
}

void GreySquareActor::doUpdate(const oxygine::UpdateState& us)
{
   applyMoveSpeed(us);
   Point oldLocation = GetLocation();
   Update(us);
   Point newLocation = GetLocation();

   GameEngine::getInstance().checkGraySquareActorLocation(this, oldLocation, newLocation);
   setPosition(GetLocation().x.Value(), GetLocation().y.Value());
}

void GreySquareActor::applyMoveSpeed(const oxygine::UpdateState& us)
{
   auto speed = GetSpeed();
   const auto speedDif = getTime(us) * horizontalMoveAcceleration_.Abs();

   if(moveDirection_ == Direction::Right)
   {
      speed.x = std::min(maxHorizontalSpeed_.Abs().Value(), (speed.x + speedDif).Value()) * pixelPerSecond;
   }
   else if (moveDirection_ == Direction::Right || moveDirection_ == Direction::Left)
   {
      speed.x = std::max(-(maxHorizontalSpeed_.Abs().Value()), (speed.x - speedDif).Value()) * pixelPerSecond;
   }
   else if (moveDirection_ == Direction::NotChanged)
   {
      const int sign = speed.x.Value() >= 0 ? 1 : -1;
      auto newModuleOfSpeed = std::max((speed.x.Abs() - speedDif.Abs()).Value(), 0.0) * pixelPerSecond;
      speed.x = sign * newModuleOfSpeed;
   }

   SetSpeed(speed);
}

void GreySquareActor::Jump()
{
   auto speed = GetSpeed();
   if(speed.y.Value() > 0) speed.y *= 0;
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
