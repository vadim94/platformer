#pragma once

#include "math/vector2.h"

#include "PhysicalObject.h"
#include "Unit.h"

namespace PlatformerTest
{
   static oxygine::UpdateState GetUpdateStruct(double seconds)
   {
      oxygine::UpdateState update;
      update.dt = static_cast<oxygine::timeMS>(seconds * 1000);
      return update;
   }

   static oxygine::UpdateState GetUpdateStruct(Time seconds)
   {
      return GetUpdateStruct(seconds.Value());
   }

	static const oxygine::UpdateState kOneSecondUpdateStruct = GetUpdateStruct(1);
	static const oxygine::UpdateState kHalfSecondUpdateStruct = GetUpdateStruct(0.5);

	static const PhysicalObject::Point kOneUnitHorizontalyAndVertically{ kPixel, kPixel };
	static const PhysicalObject::Point kSomeLocation = kOneUnitHorizontalyAndVertically;
	static const PhysicalObject::Point kZeroPoint{ Distance(0), Distance(0) };
	static const PhysicalObject::Point kOneUnitHorisontallyPoint{ Distance(1), Distance(0) };

	static const PhysicalObject::SpeedVector kZeroSpeed{ Speed(0), Speed(0) };
	static const PhysicalObject::SpeedVector kOneUnitPerSecondHorizontally{ kPixelPerSecond, Speed(0) };
	static const PhysicalObject::SpeedVector kOneUnitPerSecondVertically{ Speed(0), kPixelPerSecond };
	static const PhysicalObject::AccelerationVector kZeroAccelerationVector{ Acceleration(0), Acceleration(0) };
	static const PhysicalObject::AccelerationVector kOneUnitPerSecondSquaredVertically{ Acceleration(0), kPixelPerSquareSecond };
	static const PhysicalObject::AccelerationVector kOneUnitPerSecondSquaredHorizontally{ kPixelPerSquareSecond, Acceleration(0) };
	static const PhysicalObject::AccelerationVector kOneUnitPerSecondSquaredVerticallyAndHorizontally{ Acceleration(0), Acceleration(0) };
}