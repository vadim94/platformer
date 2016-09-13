#pragma once

#include "ColorRectSprite.h"

#include "vector"

#include "math/color.h"

#include "ButtonAlignerActor.h"



DECLARE_SMART(PauseMenuActor, spPauseMenuActor);
class PauseMenuActor : public oxygine::ColorRectSprite
{
public:
	PauseMenuActor();
	void Toggle();
	bool IsShown() const;

private:
	void show();
	void hide();
	void addButtons();
	void setupMenuVisualParameters();

private:
	static const oxygine::Color backgroundColor_;

	spButtonAlignerActor buttonFormatter_;
};

