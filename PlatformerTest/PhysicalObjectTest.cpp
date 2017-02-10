#include "stdafx.h"
#include "CppUnitTest.h"

#include "math/vector2.h"

#include "PhysicalObjectForTest.h"
#include "PhysicConstants.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlatformerTest
{
   TEST_CLASS(TestOfPhysicalObject)
   {
   public:

      TEST_METHOD(ConstructedWithZeroSpeedAndZeroPointLocation)
      {
         PhysicalObjectForTest object;

         Assert::IsTrue(zeroPoint == object.GetLocation());
         Assert::IsTrue(zeroSpeed == object.GetSpeed());
      }

      TEST_METHOD(ConstructedWithLocation)
      {
         PhysicalObjectForTest object(someLocation);

         Assert::IsTrue(someLocation == object.GetLocation());
      }

      TEST_METHOD(MovesWhenNonZeroSpeed)
      {
         PhysicalObject::SetGravity(zeroAccelerationVector);
         PhysicalObjectForTest object;
         object.SetSpeed(oneUnitPerSecondHorizontally);

         object.CalculateNewLocation(oneSecondUpdateStruct);

         Assert::IsTrue(oneUnitHorisontallyPoint == object.GetLocation());
      }

      TEST_METHOD(MovesWithGravity)
      {
         PhysicalObject::SetGravity(oneUnitPerSecondSquaredVertically);
         PhysicalObjectForTest object;
         object.SetSpeed(oneUnitPerSecondHorizontally);

         object.CalculateNewLocation(oneSecondUpdateStruct);

         Assert::IsTrue(oneUnitHorizontalyAndVertically == object.GetLocation());
      }

      TEST_METHOD(MovesWithGravityAndCustomAcceleration)
      {
         PhysicalObject::SetGravity(oneUnitPerSecondSquaredVertically);
         PhysicalObjectForTest object;
         object.SetAcceleration(oneUnitPerSecondSquaredHorizontally);

         object.CalculateNewLocation(oneSecondUpdateStruct);

         Assert::IsTrue(oneUnitHorizontalyAndVertically == object.GetLocation());
      }

   };
}