#pragma once

#include "math/vector2.h"
#include "UpdateState.h"
#include "Unit.h"

class PhysicalObject
{
public:

   using Point = oxygine::VectorT2 < Distance > ;
   using SpeedVector = oxygine::VectorT2 < Speed > ;
   using AccelerationVector = oxygine::VectorT2 < Acceleration > ;

   PhysicalObject(const Point& location);
   PhysicalObject() = default;
   virtual ~PhysicalObject() = default;

   void SetAcceleration(const AccelerationVector& newAcceleration);
   const AccelerationVector& GetAcceleration();

   void SetSpeed(const SpeedVector& newSpeed);
   const SpeedVector& GetSpeed() const;

   const Point& GetLocation() const;

   void Update(const oxygine::UpdateState& updateState);

   void SetLocation(const Point& newLocation);

   static const AccelerationVector& GetGravity();
   static void SetGravity(const AccelerationVector& newGravity);

private:

   SpeedVector updateSpeed(const oxygine::UpdateState& updateState);
   Point updatePosition(const oxygine::UpdateState& updateState, const SpeedVector& newSpeed);

private:
   Point location_;
   SpeedVector speed_;
   AccelerationVector acceleration_;

   static AccelerationVector gravityAcceleration_;
};

