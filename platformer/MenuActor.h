#pragma once

#include "ColorRectSprite.h"

#include "vector"

#include "math/color.h"

#include "ButtonAlignerActor.h"



DECLARE_SMART(MenuActor, spMenuActor);
class MenuActor : public oxygine::ColorRectSprite
{
public:
	MenuActor();
	void Toggle();

private:
	bool isShown() const;
	void show();
	void hide();
	void addButtons();
	void setupMenuVisualParameters();

private:
	static const oxygine::Color backgroundColor_;

	spButtonAlignerActor buttonFormatter_;
};

