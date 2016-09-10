#include "stdafx.h"
#include "CppUnitTest.h"

#include "math/vector2.h"

#include "PhysicalObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace
{
   oxygine::UpdateState oneSecondUpdate()
   {
      oxygine::UpdateState update;
      update.dt = 1000;
      return update;
   }

   static const oxygine::UpdateState oneSecondUpdateStruct = oneSecondUpdate();

   static const PhysicalObject::Point oneUnitHorizontalyAndVertically{ pixel, pixel };
   static const PhysicalObject::Point someLocation = oneUnitHorizontalyAndVertically;
   static const PhysicalObject::Point zeroPoint{ Distance(0), Distance(0) };
   static const PhysicalObject::Point oneUnitHorisontallyPoint{ Distance(1), Distance(0) };

   static const PhysicalObject::SpeedVector zeroSpeed{ Speed(0), Speed(0) };
   static const PhysicalObject::SpeedVector oneUnitPerSecondHorizontally{ pixelPerSecond, Speed(0) };
   static const PhysicalObject::AccelerationVector zeroAccelerationVector{ Acceleration(0), Acceleration(0) };
   static const PhysicalObject::AccelerationVector oneUnitPerSecondSquaredVertically{ Acceleration(0), pixelPerSquareSecond };
   static const PhysicalObject::AccelerationVector oneUnitPerSecondSquaredHorizontally{ pixelPerSquareSecond, Acceleration(0)};
}

namespace PlatformerTest
{
   TEST_CLASS(TestOfPhysicalObject)
   {
   public:

      TEST_METHOD(ConstructedWithZeroSpeedAndZeroPointLocation)
      {
         PhysicalObject object;

         Assert::IsTrue(zeroPoint == object.GetLocation());
         Assert::IsTrue(zeroSpeed == object.GetSpeed());
      }

      TEST_METHOD(ConstructedWithLocation)
      {
         PhysicalObject object(someLocation);

         Assert::IsTrue(someLocation == object.GetLocation());
      }

      TEST_METHOD(SetSpeed)
      {
         PhysicalObject object;
         object.SetSpeed(oneUnitPerSecondHorizontally);

         Assert::IsTrue(oneUnitPerSecondHorizontally == object.GetSpeed());
      }

      TEST_METHOD(SetGravity)
      {
         PhysicalObject::SetGravity(oneUnitPerSecondSquaredVertically);

         Assert::IsTrue(PhysicalObject::GetGravity() == oneUnitPerSecondSquaredVertically);
      }

      TEST_METHOD(MovesWhenNonZeroSpeed)
      {
         PhysicalObject::SetGravity(zeroAccelerationVector);
         PhysicalObject object;
         object.SetSpeed(oneUnitPerSecondHorizontally);

         object.Update(oneSecondUpdateStruct);

         Assert::IsTrue(oneUnitHorisontallyPoint == object.GetLocation());
      }

      TEST_METHOD(MovesWithGravity)
      {
         PhysicalObject::SetGravity(oneUnitPerSecondSquaredVertically);
         PhysicalObject object;
         object.SetSpeed(oneUnitPerSecondHorizontally);

         object.Update(oneSecondUpdateStruct);

         Assert::IsTrue(oneUnitHorizontalyAndVertically == object.GetLocation());
      }

      TEST_METHOD(MovesWithGravityAndCustomAcceleration)
      {
         PhysicalObject::SetGravity(oneUnitPerSecondSquaredVertically);
         PhysicalObject object;
         object.SetAcceleration(oneUnitPerSecondSquaredHorizontally);

         object.Update(oneSecondUpdateStruct);

         Assert::IsTrue(oneUnitHorizontalyAndVertically == object.GetLocation());
      }

   };
}