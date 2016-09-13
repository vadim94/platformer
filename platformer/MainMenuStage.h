#pragma once
#include "Stage.h"

#include "ButtonAlignerActor.h"

class MainMenuStage : public oxygine::Stage
{
public:
	MainMenuStage(const oxygine::Vector2& size);

private:
	void addButtons(spButtonAlignerActor mainMenuButtons);
	void align(spButtonAlignerActor mainMenuButtons);
};

