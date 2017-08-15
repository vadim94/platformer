#include "stdafx.h"
#include "CppUnitTest.h"

#include "PhysicConstants.h"
#include "ToStringOverloads.h"

#include "GreySquareActor.h"
#include "Direction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
    Time GetTimeNotEnoughToAccelerateToMaxSpeed()
    {
        return GreySquareActor::GetMaxHorizontalSpeed().Abs() / GreySquareActor::GetMaxHorizontalMoveAcceleration().Abs() / 2;
    }

    Speed CalculateSpeedDiff()
    {
        return GreySquareActor::GetMaxHorizontalMoveAcceleration().Abs() * GetTimeNotEnoughToAccelerateToMaxSpeed();
    }

    PhysicalObject::SpeedVector GetSpeedVectorWithMaxPositiveHorizontalSpeed()
    {
        return{ GreySquareActor::GetMaxHorizontalSpeed().Abs() , 0 * kPixelPerSecond };
    }

    PhysicalObject::SpeedVector GetSpeedVectorWithMaxNegativeHorizontalSpeed()
    {
        auto maxPositive = GetSpeedVectorWithMaxPositiveHorizontalSpeed();
        return{ -maxPositive.x , maxPositive.y };
    }

    const auto kEnoughTimeToFullstop = PlatformerTest::GetUpdateStruct(10);
    const auto kALotOftime = PlatformerTest::GetUpdateStruct(10);
}

namespace PlatformerTest
{
    TEST_CLASS(TestOfSquareActor)
    {
    public:
        TEST_METHOD_INITIALIZE(init)
        {
            actor_ = new GreySquareActor({ kPixel * 0, kPixel * 0 });
            GreySquareActor::SetGravity(kZeroAccelerationVector);
        }

        TEST_METHOD(MoveHorizontallyThrowsIfDirectionNotHorizontal)
        {
            auto move_up = [this]() {actor_->MoveHorizontally(Direction::kUp); };
            auto move_down = [this]() {actor_->MoveHorizontally(Direction::kDown); };
            auto move_none = [this]() {actor_->MoveHorizontally(Direction::kNotChanged); };

            Assert::ExpectException<std::logic_error>(move_up);
            Assert::ExpectException<std::logic_error>(move_down);
            Assert::ExpectException<std::logic_error>(move_none);
        }

        TEST_METHOD(StartAcceleratingAfterMoveHorizontallyCall)
        {
            GreySquareActor actor_accelerates_left{ *actor_ };
            GreySquareActor actor_accelerates_right{ *actor_ };
            actor_accelerates_left.MoveHorizontally(Direction::kLeft);
            actor_accelerates_right.MoveHorizontally(Direction::kRight);
            actor_accelerates_left.doUpdate(GetUpdateStruct(GetTimeNotEnoughToAccelerateToMaxSpeed()));
            actor_accelerates_right.doUpdate(GetUpdateStruct(GetTimeNotEnoughToAccelerateToMaxSpeed()));

            Assert::AreEqual(CalculateSpeedDiff(), actor_accelerates_right.GetSpeed().x);
            Assert::AreEqual(-CalculateSpeedDiff(), actor_accelerates_left.GetSpeed().x);
        }

        TEST_METHOD(ReachMaxSpeedAfterSomeTimeMoveHorizontally)
        {
            GreySquareActor actor_accelerates_left{ *actor_ };
            GreySquareActor actor_accelerates_right{ *actor_ };

            actor_accelerates_left.MoveHorizontally(Direction::kLeft);
            actor_accelerates_right.MoveHorizontally(Direction::kRight);
            actor_accelerates_left.doUpdate(kALotOftime);
            actor_accelerates_right.doUpdate(kALotOftime);

            Assert::AreEqual(GreySquareActor::GetMaxHorizontalSpeed(), actor_accelerates_right.GetSpeed().x);
            Assert::AreEqual(-GreySquareActor::GetMaxHorizontalSpeed(), actor_accelerates_left.GetSpeed().x);
        }

        TEST_METHOD(SpeedDecresesOvertimeWhenStopMoveCalled)
        {
            GreySquareActor actor_moving_left{ *actor_ };
            GreySquareActor actor_moving_right{ *actor_ };
            actor_moving_right.MoveHorizontally(Direction::kRight);
            actor_moving_left.MoveHorizontally(Direction::kLeft);
            actor_moving_right.SetSpeed(GetSpeedVectorWithMaxPositiveHorizontalSpeed());
            actor_moving_left.SetSpeed(GetSpeedVectorWithMaxNegativeHorizontalSpeed());

            actor_moving_left.StopMoveHorizontally();
            actor_moving_right.StopMoveHorizontally();
            actor_moving_left.doUpdate(GetUpdateStruct(GetTimeNotEnoughToAccelerateToMaxSpeed()));
            actor_moving_right.doUpdate(GetUpdateStruct(GetTimeNotEnoughToAccelerateToMaxSpeed()));

            Assert::AreEqual(GreySquareActor::GetMaxHorizontalSpeed() - CalculateSpeedDiff(), actor_moving_right.GetSpeed().x);
            Assert::AreEqual(-GreySquareActor::GetMaxHorizontalSpeed() + CalculateSpeedDiff(), actor_moving_left.GetSpeed().x);
        }

        TEST_METHOD(SpeedBecomesZeroAfterSomeTimeWhenStopMoveCalled)
        {
            GreySquareActor actor_moving_left{ *actor_ };
            GreySquareActor actor_moving_right{ *actor_ };
            actor_moving_right.MoveHorizontally(Direction::kRight);
            actor_moving_left.MoveHorizontally(Direction::kLeft);
            actor_moving_right.SetSpeed(GetSpeedVectorWithMaxPositiveHorizontalSpeed());
            actor_moving_left.SetSpeed(GetSpeedVectorWithMaxNegativeHorizontalSpeed());

            actor_moving_left.StopMoveHorizontally();
            actor_moving_right.StopMoveHorizontally();
            actor_moving_left.doUpdate(kEnoughTimeToFullstop);
            actor_moving_right.doUpdate(kEnoughTimeToFullstop);

            Assert::AreEqual(kZeroSpeed, actor_moving_right.GetSpeed());
            Assert::AreEqual(kZeroSpeed, actor_moving_left.GetSpeed());
        }


    private:
        spGreySquareActor actor_;
    };
}