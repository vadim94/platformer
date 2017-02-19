#pragma once
#include "Stage.h"

#include "PauseMenuActor.h"
#include "EndGameActor.h"
#include "EnvironmentScroller.h"
#include "Unit.h"
#include "PhysicalObject.h"

class GameStage : public oxygine::Stage
{
public:
	GameStage(const oxygine::Vector2& size);

private:
	void CreateAndAddSquare();
	void CreateAndAddAllGround();
   void CreateAndAddGround(const PhysicalObject::Point& point);
	void CreateAndAddMenu();
	bool IsPaused();
	bool IsEnded();
   void ScrollIfNeeded(const PhysicalObject::Point& location_of_active_object);
private:
	spPauseMenuActor pause_menu_;
	spEndGameActor end_game_;
   EnvironmentScroller scroller_;

   static const Distance kScrollBuffer;
};

