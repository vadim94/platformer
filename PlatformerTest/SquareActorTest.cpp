#include "stdafx.h"
#include "CppUnitTest.h"

#include "PhysicConstants.h"
#include "ToStringOverloads.h"

#include "GreySquareActor.h"
#include "Direction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
   Time getTimeNotEnoughToAccelerateToMaxSpeed()
   {
      return GreySquareActor::GetMaxHorizontalSpeed().Abs() / GreySquareActor::GetMaxHorizontalMoveAcceleration().Abs() / 2;
   }

   Speed calculateSpeedDiff()
   {
      return GreySquareActor::GetMaxHorizontalMoveAcceleration().Abs() * getTimeNotEnoughToAccelerateToMaxSpeed();
   }

   PhysicalObject::SpeedVector getSpeedVectorWithMaxPositiveHorizontalSpeed()
   {
      return{ GreySquareActor::GetMaxHorizontalSpeed().Abs() , 0 * pixelPerSecond };
   }

   PhysicalObject::SpeedVector getSpeedVectorWithMaxNegativeHorizontalSpeed()
   {
      auto maxPositive = getSpeedVectorWithMaxPositiveHorizontalSpeed();
      return{ -maxPositive.x , maxPositive.y };
   }

   const auto enoughTimeToFullstop = PlatformerTest::getUpdateStruct(10);
   const auto aLotOftime = PlatformerTest::getUpdateStruct(10);
}

namespace PlatformerTest
{
	TEST_CLASS(TestOfSquareActor)
	{
	public:
		TEST_METHOD_INITIALIZE(init)
		{
			actor_ = new GreySquareActor({ pixel * 0, pixel * 0 });
			GreySquareActor::SetGravity(zeroAccelerationVector);
		}

		TEST_METHOD(MoveHorizontallyThrowsIfDirectionNotHorizontal)
		{
			auto moveUp = [this]() {actor_->MoveHorizontally(Direction::Up); };
			auto moveDown = [this]() {actor_->MoveHorizontally(Direction::Down); };
			auto moveNone = [this]() {actor_->MoveHorizontally(Direction::NotChanged); };

			Assert::ExpectException<std::logic_error>(moveUp);
			Assert::ExpectException<std::logic_error>(moveDown);
			Assert::ExpectException<std::logic_error>(moveNone);
		}

      TEST_METHOD(StartAcceleratingAfterMoveHorizontallyCall)
      {
         GreySquareActor actorAcceleratesLeft{ *actor_ };
         GreySquareActor actorAcceleratesRight{ *actor_ };
         actorAcceleratesLeft.MoveHorizontally(Direction::Left);
         actorAcceleratesRight.MoveHorizontally(Direction::Right);
         actorAcceleratesLeft.doUpdate(getUpdateStruct(getTimeNotEnoughToAccelerateToMaxSpeed()));
         actorAcceleratesRight.doUpdate(getUpdateStruct(getTimeNotEnoughToAccelerateToMaxSpeed()));

         Assert::AreEqual(calculateSpeedDiff(), actorAcceleratesRight.GetSpeed().x);
         Assert::AreEqual(-calculateSpeedDiff(), actorAcceleratesLeft.GetSpeed().x);
      }

      TEST_METHOD(ReachMaxSpeedAfterSomeTimeMoveHorizontally)
      {
         GreySquareActor actorAcceleratesLeft{ *actor_ };
         GreySquareActor actorAcceleratesRight{ *actor_ };

         actorAcceleratesLeft.MoveHorizontally(Direction::Left);
         actorAcceleratesRight.MoveHorizontally(Direction::Right);
         actorAcceleratesLeft.doUpdate(aLotOftime);
         actorAcceleratesRight.doUpdate(aLotOftime);

         Assert::AreEqual(GreySquareActor::GetMaxHorizontalSpeed(), actorAcceleratesRight.GetSpeed().x);
         Assert::AreEqual(-GreySquareActor::GetMaxHorizontalSpeed(), actorAcceleratesLeft.GetSpeed().x);
      }

      TEST_METHOD(SpeedDecresesOvertimeWhenStopMoveCalled)
      {
         GreySquareActor actorMovingLeft{ *actor_ };
         GreySquareActor actorMovingRight{ *actor_ };
         actorMovingRight.MoveHorizontally(Direction::Right);
         actorMovingLeft.MoveHorizontally(Direction::Left);
         actorMovingRight.SetSpeed(getSpeedVectorWithMaxPositiveHorizontalSpeed());
         actorMovingLeft.SetSpeed(getSpeedVectorWithMaxNegativeHorizontalSpeed());

         actorMovingLeft.StopMoveHorizontally();
         actorMovingRight.StopMoveHorizontally();
         actorMovingLeft.doUpdate(getUpdateStruct(getTimeNotEnoughToAccelerateToMaxSpeed()));
         actorMovingRight.doUpdate(getUpdateStruct(getTimeNotEnoughToAccelerateToMaxSpeed()));

         Assert::AreEqual(GreySquareActor::GetMaxHorizontalSpeed() - calculateSpeedDiff(), actorMovingRight.GetSpeed().x);
         Assert::AreEqual(-GreySquareActor::GetMaxHorizontalSpeed() + calculateSpeedDiff(), actorMovingLeft.GetSpeed().x);
      }

      TEST_METHOD(SpeedBecomesZeroAfterSomeTimeWhenStopMoveCalled)
      {
         GreySquareActor actorMovingLeft{ *actor_ };
         GreySquareActor actorMovingRight{ *actor_ };
         actorMovingRight.MoveHorizontally(Direction::Right);
         actorMovingLeft.MoveHorizontally(Direction::Left);
         actorMovingRight.SetSpeed(getSpeedVectorWithMaxPositiveHorizontalSpeed());
         actorMovingLeft.SetSpeed(getSpeedVectorWithMaxNegativeHorizontalSpeed());

         actorMovingLeft.StopMoveHorizontally();
         actorMovingRight.StopMoveHorizontally();
         actorMovingLeft.doUpdate(enoughTimeToFullstop);
         actorMovingRight.doUpdate(enoughTimeToFullstop);

         Assert::AreEqual(zeroSpeed, actorMovingRight.GetSpeed());
         Assert::AreEqual(zeroSpeed, actorMovingLeft.GetSpeed());
      }


	private:
		spGreySquareActor actor_;
	};
}