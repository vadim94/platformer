#include "GreySquareActor.h"
#include "GameEngine.h"
#include "Direction.h"
#include "MoveEvent.h"
#include "Stage.h"

const PhysicalObject::SpeedVector GreySquareActor::kJumpSpeed{ kPixelPerSecond * 0, kPixelPerSecond * -400 };
const Speed GreySquareActor::kMaxHorizontalSpeed{ kPixelPerSecond * 500 };
const Acceleration GreySquareActor::kHorizontalMoveAcceleration{ kPixelPerSquareSecond * 2000 };

namespace
{
   Time getTime(const oxygine::UpdateState& us)
   {
      return us.dt / 1000.0 * kSecond;
   }
}

GreySquareActor::GreySquareActor(const PhysicalObject::Point& start_point) : move_direction_{ Direction::kNotChanged }
{
   setColor(oxygine::Color::Silver);
   SetLocation(start_point);
   setSize(100, 100);
}

void GreySquareActor::doUpdate(const oxygine::UpdateState& us)
{
   ApplyMoveSpeed(us);
   Point old_location = GetLocation();
   CalculateNewLocation(us);
   Point projected_location = GetLocation();

   MoveEvent event{this, old_location, projected_location };
   if (oxygine::Stage::instance) // Is null during tests.
   {
      oxygine::Stage::instance->dispatchEvent(&event);
   }
}

void GreySquareActor::ApplyMoveSpeed(const oxygine::UpdateState& us)
{
   auto speed = GetSpeed();
   const auto speed_dif = getTime(us) * kHorizontalMoveAcceleration.Abs();

   if(move_direction_ == Direction::kRight)
   {
      speed.x = std::min(kMaxHorizontalSpeed.Abs(), (speed.x + speed_dif));
   }
   else if (move_direction_ == Direction::kRight || move_direction_ == Direction::kLeft)
   {
      speed.x = std::max(-(kMaxHorizontalSpeed.Abs()), (speed.x - speed_dif));
   }
   else if (move_direction_ == Direction::kNotChanged)
   {
      const int sign = speed.x.Value() >= 0 ? 1 : -1;
      auto new_module_of_speed = std::max((speed.x.Abs() - speed_dif.Abs()), 0 * kPixelPerSecond);
      speed.x = sign * new_module_of_speed;
   }

   SetSpeed(speed);
}

void GreySquareActor::Jump()
{
   auto speed = GetSpeed();
   if(speed.y > 0 * kPixelPerSecond) speed.y *= 0;
   SetSpeed(speed + kJumpSpeed);
}

void GreySquareActor::MoveHorizontally(Direction dir)
{
   if (dir == Direction::kNotChanged || dir == Direction::kUp || dir == Direction::kDown)
      throw std::logic_error("can move only horizontally");

   move_direction_ = dir;
}

void GreySquareActor::StopMoveHorizontally()
{
   move_direction_ = Direction::kNotChanged;
}