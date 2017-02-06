#pragma once

#include "ColorRectSprite.h"

#include "ButtonAlignerActor.h"

DECLARE_SMART(EndGameActor, spEndGameActor);
class EndGameActor : public oxygine::ColorRectSprite
{
public:
	EndGameActor();
	void show();
	bool isShown() const;

private:
	void addButtons(spButtonAlignerActor endGameStageButtons);
	void align(spButtonAlignerActor endGameStageButtons);

private:
	static const oxygine::Color backgroundColor_;
};

