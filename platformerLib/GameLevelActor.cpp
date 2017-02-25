#include "GameLevelActor.h"

Distance GameLevelActor::kScrollBuffer = kPixel * 200;

GameLevelActor::GameLevelActor(const PhysicalObject::Size& size) : stage_size_{ size }
{
   SetSize(size);
}

void GameLevelActor::AddAndExtend(const spActorBase& actor)
{
   addChild(actor);
   ExtendToInclude(*actor);
}

void GameLevelActor::ExtendToInclude(const PhysicalObject& object)
{
   auto object_position = object.GetLocation();
   auto object_size = object.GetSize();
   auto level_size = GetSize();
   level_size.x = std::max(level_size.x, object_position.x + object_size.x);
   SetSize(level_size);
}

void GameLevelActor::ScrollToShow(const PhysicalObject::Point& point)
{
   auto level_location = GetLocation();
   auto point_relative_to_stage = point + level_location;
   Distance distance_to_stage_right_border = stage_size_.x - point_relative_to_stage.x;
   Distance distance_to_stage_left_border = point_relative_to_stage.x;
   Distance move_to_left = distance_to_stage_right_border - kScrollBuffer;
   Distance move_to_right = kScrollBuffer - distance_to_stage_left_border;

   auto new_level_location = level_location;
   if (move_to_left < 0 * kPixel)
   {
      new_level_location.x += move_to_left;
   }
   else if (move_to_right > 0 * kPixel)
   {
      new_level_location.x += move_to_right;
   }
   SetLocation(new_level_location);
}
