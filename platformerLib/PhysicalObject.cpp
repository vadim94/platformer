#include "PhysicalObject.h"
#include <cmath>

PhysicalObject::AccelerationVector PhysicalObject::gravityAcceleration_{ pixelPerSquareSecond * 0, pixelPerSquareSecond * 800 };

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

void PhysicalObject::CalculateNewLocation(const oxygine::UpdateState& updateState)
{
   auto newSpeed = updateSpeed(updateState);
   auto newPosition = updatePosition(updateState, newSpeed);

   SetLocation(newPosition);
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
   auto newLocation = GetLocation();
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