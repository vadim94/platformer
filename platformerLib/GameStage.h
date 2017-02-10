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
	void createAndAddSquare();
	void createAndAddAllGround();
   void createAndAddGround(const PhysicalObject::Point& point);
	void createAndAddMenu();
	bool isPaused();
	bool isEnded();
   void scrollIfNeeded(const PhysicalObject::Point& locationOfActiveObject);
private:
	spPauseMenuActor pauseMenu_;
	spEndGameActor endGame_;
   EnvironmentScroller scroller_;

   static const Distance scrollBuffer_;
};

