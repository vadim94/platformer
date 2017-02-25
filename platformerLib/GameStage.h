#pragma once
#include "Stage.h"

#include "PauseMenuActor.h"
#include "EndGameActor.h"
#include "Unit.h"
#include "PhysicalObject.h"
#include "GameLevelActor.h"

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
private:
	spPauseMenuActor pause_menu_;
	spEndGameActor end_game_;
   spGameLevelActor game_level_;
};

