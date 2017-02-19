#pragma once

#include "ColorRectSprite.h"

#include "ButtonAlignerActor.h"

DECLARE_SMART(EndGameActor, spEndGameActor);
class EndGameActor : public oxygine::ColorRectSprite
{
public:
	EndGameActor();
	void Show();
	bool IsShown() const;

private:
	void AddButtons(spButtonAlignerActor end_game_stage_buttons);
	void Align(spButtonAlignerActor end_game_stage_buttons);

private:
	static const oxygine::Color kBackgroundColor;
};

