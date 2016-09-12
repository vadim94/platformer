#include "MenuActor.h"

#include "Stage.h"
#include "Clock.h"
#include "TouchEvent.h"
#include "core/oxygine.h"

const oxygine::Color MenuActor::backgroundColor_ = oxygine::Color(255, 0, 0, 100);

MenuActor::MenuActor() : buttonFormatter_(new ButtonAlignerActor)
{
	addButtons();
	setupMenuVisualParameters();
}

void MenuActor::setupMenuVisualParameters()
{
	setVisible(false);
	setSize(oxygine::getStage()->getSize());
	setColor(backgroundColor_);

	const oxygine::Vector2 buttonFormatterTopLeft = (oxygine::getStage()->getSize() - buttonFormatter_->getSize()) / 2;
	buttonFormatter_->setPosition(buttonFormatterTopLeft);
	addChild(buttonFormatter_);
}

void MenuActor::addButtons()
{
	buttonFormatter_->AddButton("Continue")
		->addEventListener(oxygine::TouchEvent::CLICK, [this](oxygine::Event*) { Toggle(); });
	buttonFormatter_->AddButton("Exit")
		->addEventListener(oxygine::TouchEvent::CLICK, [this](oxygine::Event*) { oxygine::core::requestQuit(); });
}

void MenuActor::Toggle()
{
	if (isShown())
	{
		hide();
	}
	else
	{
		show();
	}
}

bool MenuActor::isShown() const
{
	return getVisible();
}

void MenuActor::show()
{
	oxygine::getStage()->getClock()->pause();
	setVisible(true);
}

void MenuActor::hide()
{
	oxygine::getStage()->getClock()->resume();
	setVisible(false);
}