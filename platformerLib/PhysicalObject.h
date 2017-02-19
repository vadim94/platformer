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

   void SetAcceleration(const AccelerationVector& new_acceleration);
   const AccelerationVector& GetAcceleration();

   void SetSpeed(const SpeedVector& new_speed);
   const SpeedVector& GetSpeed() const;

   void CalculateNewLocation(const oxygine::UpdateState& update_state);

   virtual Point GetLocation() const = 0;
   virtual void SetLocation(const Point& new_location) = 0;
   virtual Size GetSize() const = 0;
   virtual void SetSize(const Size& size) = 0;

   static const AccelerationVector& GetGravity();
   static void SetGravity(const AccelerationVector& new_gravity);

private:

   SpeedVector UpdateSpeed(const oxygine::UpdateState& update_state);
   Point UpdatePosition(const oxygine::UpdateState& update_state, const SpeedVector& new_speed);

private:
   SpeedVector speed_;
   AccelerationVector acceleration_;
   static AccelerationVector gravity_acceleration_;
};

