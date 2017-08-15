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

            Assert::IsTrue(kZeroPoint == object.GetLocation());
            Assert::IsTrue(kZeroSpeed == object.GetSpeed());
        }

        TEST_METHOD(ConstructedWithLocation)
        {
            PhysicalObjectForTest object(kSomeLocation);

            Assert::IsTrue(kSomeLocation == object.GetLocation());
        }

        TEST_METHOD(MovesWhenNonZeroSpeed)
        {
            PhysicalObject::SetGravity(kZeroAccelerationVector);
            PhysicalObjectForTest object;
            object.SetSpeed(kOneUnitPerSecondHorizontally);

            object.CalculateNewLocation(kOneSecondUpdateStruct);

            Assert::IsTrue(kOneUnitHorisontallyPoint == object.GetLocation());
        }

        TEST_METHOD(MovesWithGravity)
        {
            PhysicalObject::SetGravity(kOneUnitPerSecondSquaredVertically);
            PhysicalObjectForTest object;
            object.SetSpeed(kOneUnitPerSecondHorizontally);

            object.CalculateNewLocation(kOneSecondUpdateStruct);

            Assert::IsTrue(kOneUnitHorizontalyAndVertically == object.GetLocation());
        }

        TEST_METHOD(MovesWithGravityAndCustomAcceleration)
        {
            PhysicalObject::SetGravity(kOneUnitPerSecondSquaredVertically);
            PhysicalObjectForTest object;
            object.SetAcceleration(kOneUnitPerSecondSquaredHorizontally);

            object.CalculateNewLocation(kOneSecondUpdateStruct);

            Assert::IsTrue(kOneUnitHorizontalyAndVertically == object.GetLocation());
        }

    };
}