#include "PhysicalObject.h"
#include <cmath>

PhysicalObject::AccelerationVector PhysicalObject::gravity_acceleration_{ kPixelPerSquareSecond * 0, kPixelPerSquareSecond * 800 };

const PhysicalObject::SpeedVector& PhysicalObject::GetSpeed() const
{
   return speed_;
}

void PhysicalObject::SetSpeed(const PhysicalObject::SpeedVector& new_speed)
{
   speed_ = new_speed;
}

void PhysicalObject::SetAcceleration(const AccelerationVector& new_acceleration)
{
   acceleration_ = new_acceleration;
}

const PhysicalObject::AccelerationVector& PhysicalObject::GetAcceleration()
{
   return acceleration_;
}

void PhysicalObject::CalculateNewLocation(const oxygine::UpdateState& update_state)
{
   auto new_speed = UpdateSpeed(update_state);
   auto new_position = UpdatePosition(update_state, new_speed);

   SetLocation(new_position);
   speed_ = new_speed;
}

PhysicalObject::SpeedVector PhysicalObject::UpdateSpeed(const oxygine::UpdateState& update_state)
{
   auto new_speed = speed_;
   new_speed.x += (acceleration_.x + gravity_acceleration_.x) * Time(update_state.dt / 1000.0);
   new_speed.y += (acceleration_.y + gravity_acceleration_.y) * Time(update_state.dt / 1000.0);
   return new_speed;
}

PhysicalObject::Point PhysicalObject::UpdatePosition(const oxygine::UpdateState& update_state,
   const PhysicalObject::SpeedVector& new_speed)
{
   auto new_location = GetLocation();
   new_location.x += new_speed.x * Time(update_state.dt / 1000.0);
   new_location.y += new_speed.y * Time(update_state.dt / 1000.0);
   return new_location;
}

const PhysicalObject::AccelerationVector& PhysicalObject::GetGravity()
{
   return gravity_acceleration_;
}

void PhysicalObject::SetGravity(const PhysicalObject::AccelerationVector& new_gravity)
{
   gravity_acceleration_ = new_gravity;
}