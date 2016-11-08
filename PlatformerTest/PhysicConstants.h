#pragma once

#include "math/vector2.h"

#include "PhysicalObject.h"
#include "Unit.h"

namespace PlatformerTest
{
   static oxygine::UpdateState getUpdateStruct(double seconds)
   {
      oxygine::UpdateState update;
      update.dt = static_cast<oxygine::timeMS>(seconds * 1000);
      return update;
   }

   static oxygine::UpdateState getUpdateStruct(Time seconds)
   {
      return getUpdateStruct(seconds.Value());
   }

	static const oxygine::UpdateState oneSecondUpdateStruct = getUpdateStruct(1);
	static const oxygine::UpdateState halfSecondUpdateStruct = getUpdateStruct(0.5);

	static const PhysicalObject::Point oneUnitHorizontalyAndVertically{ pixel, pixel };
	static const PhysicalObject::Point someLocation = oneUnitHorizontalyAndVertically;
	static const PhysicalObject::Point zeroPoint{ Distance(0), Distance(0) };
	static const PhysicalObject::Point oneUnitHorisontallyPoint{ Distance(1), Distance(0) };

	static const PhysicalObject::SpeedVector zeroSpeed{ Speed(0), Speed(0) };
	static const PhysicalObject::SpeedVector oneUnitPerSecondHorizontally{ pixelPerSecond, Speed(0) };
	static const PhysicalObject::SpeedVector oneUnitPerSecondVertically{ Speed(0), pixelPerSecond };
	static const PhysicalObject::AccelerationVector zeroAccelerationVector{ Acceleration(0), Acceleration(0) };
	static const PhysicalObject::AccelerationVector oneUnitPerSecondSquaredVertically{ Acceleration(0), pixelPerSquareSecond };
	static const PhysicalObject::AccelerationVector oneUnitPerSecondSquaredHorizontally{ pixelPerSquareSecond, Acceleration(0) };
	static const PhysicalObject::AccelerationVector oneUnitPerSecondSquaredVerticallyAndHorizontally{ Acceleration(0), Acceleration(0) };
}