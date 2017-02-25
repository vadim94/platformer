#include "stdafx.h"
#include "CppUnitTest.h"

#include "GameLevelActor.h"
#include "PhysicalObjectForTest.h"
#include "ToStringOverloads.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlatformerTest
{
   TEST_CLASS(TestOfEnvironmentScroller)
   {
   public:

      TEST_METHOD(GameLevelInitalSizeEqualToSizeOfStage)
      {
         PhysicalObject::Size stage_size{ 10 * kPixel, 10 * kPixel };
         GameLevelActor level{ stage_size };

         Assert::AreEqual(stage_size, level.GetSize());
      }

      TEST_METHOD(AddAndExtendExtendsSize)
      {
         PhysicalObject::Size stage_size{ 10 * kPixel, 10 * kPixel };
         GameLevelActor level{ stage_size };

         PhysicalObject::Size actor_size{ 5 * kPixel, 5 * kPixel };
         PhysicalObject::Point actor_location { 10 * kPixel, 10 * kPixel };
         spActorBase some_actor = new ActorBase();
         some_actor->SetSize(actor_size);
         some_actor->SetLocation(actor_location);
         level.AddAndExtend(some_actor);

         PhysicalObject::Size expected_level_size{ stage_size.x + actor_size.x, stage_size.y };
         Assert::AreEqual(expected_level_size, level.GetSize());
      }

      TEST_METHOD(ScrollToShowMovesLevelPosition)
      {
         Distance scroll_buffer{ 10 };
         GameLevelActor::SetBuffer(scroll_buffer);
         PhysicalObject::Size stage_size{ 20 * kPixel, 20 * kPixel };
         GameLevelActor level{ stage_size };
         PhysicalObject::Size level_size{ 40 * kPixel, 40 * kPixel };
         level.SetSize(level_size);

         level.ScrollToShow({ 15 * kPixel, 30 * kPixel });
         PhysicalObject::Size scroll_forward_expected_level_position{ -5 * kPixel, 0 * kPixel };
         Assert::AreEqual(scroll_forward_expected_level_position, level.GetLocation());

         level.ScrollToShow({ 10 * kPixel, 0 * kPixel });
         PhysicalObject::Size scroll_backward_expected_level_position{ 0 * kPixel, 0 * kPixel };
         Assert::AreEqual(scroll_backward_expected_level_position, level.GetLocation());
      }
   };
}