#pragma once

#include <vector>

#include "Button.h"
#include "TextField.h"

DECLARE_SMART(ButtonAlignerActor, spButtonAlignerActor);
class ButtonAlignerActor : public oxygine::Actor
{
public:
	oxygine::spButton AddButton(const std::string& text);

private:
	oxygine::spButton createButton(const std::string& text);
	oxygine::spTextField createText(const std::string& text);
	void alignButtons();

private:
	static const int buttonPadding_;

	std::vector<oxygine::spButton> buttons_;
};

