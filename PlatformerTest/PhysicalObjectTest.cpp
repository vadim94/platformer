#include "stdafx.h"
#include "CppUnitTest.h"

#include "math/vector2.h"

#include "PhysicalObject.h"
#include "PhysicConstants.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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