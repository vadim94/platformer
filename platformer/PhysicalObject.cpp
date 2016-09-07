#include "PhysicalObject.h"
#include <cmath>

PhysicalObject::AccelerationVector PhysicalObject::gravityAcceleration_{ Acceleration(0), Acceleration(800) };

PhysicalObject::PhysicalObject(const PhysicalObject::Point& location) : location_{ location }
{
}

const PhysicalObject::Point& PhysicalObject::GetLocation() const
{
   return location_;
}

const PhysicalObject::SpeedVector& PhysicalObject::GetSpeed() const
{
   return speed_;
}

void PhysicalObject::SetSpeed(const PhysicalObject::SpeedVector& newSpeed)
{
   speed_ = newSpeed;
}

void PhysicalObject::SetAcceleration(const AccelerationVector& newAcceleration)
{
   acceleration_ = newAcceleration;
}
const PhysicalObject::AccelerationVector& PhysicalObject::GetAcceleration()
{
   return acceleration_;
}

void PhysicalObject::Update(const oxygine::UpdateState& updateState)
{
   auto newSpeed = updateSpeed(updateState);
   auto newPosition = updatePosition(updateState, newSpeed);

   location_ = newPosition;
   speed_ = newSpeed;
}

PhysicalObject::SpeedVector PhysicalObject::updateSpeed(const oxygine::UpdateState& updateState)
{
   auto newSpeed = speed_;
   newSpeed.x += (acceleration_.x + gravityAcceleration_.x) * Time(updateState.dt / 1000.0);
   newSpeed.y += (acceleration_.y + gravityAcceleration_.y) * Time(updateState.dt / 1000.0);
   return newSpeed;
}

PhysicalObject::Point PhysicalObject::updatePosition(const oxygine::UpdateState& updateState, const PhysicalObject::SpeedVector& newSpeed)
{
   auto newLocation = location_;
   newLocation.x += newSpeed.x * Time(updateState.dt / 1000.0);
   newLocation.y += newSpeed.y * Time(updateState.dt / 1000.0);
   return newLocation;
}

const PhysicalObject::AccelerationVector& PhysicalObject::GetGravity()
{
   return gravityAcceleration_;
}

void PhysicalObject::SetGravity(const PhysicalObject::AccelerationVector& newGravity)
{
   gravityAcceleration_ = newGravity;
}