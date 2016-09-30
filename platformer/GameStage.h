#pragma once
#include "Stage.h"

#include "PauseMenuActor.h"

class GameStage : public oxygine::Stage
{
public:
	GameStage(const oxygine::Vector2& size);

private:
	void createAndAddSquare();
	void createAndAddGround();
	void createAndAddMenu();
	bool isPaused();

private:
	spPauseMenuActor pauseMenu;
};

