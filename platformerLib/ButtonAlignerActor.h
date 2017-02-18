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
	oxygine::spButton CreateButton(const std::string& text);
	oxygine::spTextField CreateText(const std::string& text);
	void AlignButtons();

private:
	static const int kButtonPadding;

	std::vector<oxygine::spButton> buttons_;
};

