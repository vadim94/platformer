#pragma once
#include "Stage.h"

#include "PauseMenuActor.h"
#include "EndGameActor.h"

class GameStage : public oxygine::Stage
{
public:
	GameStage(const oxygine::Vector2& size);

private:
	void createAndAddSquare();
	void createAndAddGround();
	void createAndAddMenu();
	bool isPaused();
	bool isEnded();

private:
	spPauseMenuActor pauseMenu;
	spEndGameActor endGame;
};

