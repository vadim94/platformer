#pragma once

#include "math/vector2.h"
#include "UpdateState.h"
#include "Unit.h"

class PhysicalObject
{
public:

   using Point = oxygine::VectorT2 < Distance > ;
   using Size = Point;
   using SpeedVector = oxygine::VectorT2 < Speed > ;
   using AccelerationVector = oxygine::VectorT2 < Acceleration > ;

   PhysicalObject() = default;
   virtual ~PhysicalObject() = default;

   void SetAcceleration(const AccelerationVector& newAcceleration);
   const AccelerationVector& GetAcceleration();

   void SetSpeed(const SpeedVector& newSpeed);
   const SpeedVector& GetSpeed() const;

   void CalculateNewLocation(const oxygine::UpdateState& updateState);

   virtual Point GetLocation() const = 0;
   virtual void SetLocation(const Point& newLocation) = 0;
   virtual Size GetSize() const = 0;
   virtual void SetSize(const Size& size) = 0;

   static const AccelerationVector& GetGravity();
   static void SetGravity(const AccelerationVector& newGravity);

private:

   SpeedVector updateSpeed(const oxygine::UpdateState& updateState);
   Point updatePosition(const oxygine::UpdateState& updateState, const SpeedVector& newSpeed);

private:
   SpeedVector speed_;
   AccelerationVector acceleration_;

   static AccelerationVector gravityAcceleration_;
};

