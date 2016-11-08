#include "PauseMenuActor.h"

#include "core/oxygine.h"
#include "Stage.h"
#include "Clock.h"
#include "TouchEvent.h"
#include "DebugActor.h"

#include "MainMenuStage.h"
#include "GameStage.h"

const oxygine::Color PauseMenuActor::backgroundColor_ = oxygine::Color(255, 0, 0, 100);

PauseMenuActor::PauseMenuActor() : buttonFormatter_(new ButtonAlignerActor)
{
	addButtons();
	setupMenuVisualParameters();
}

void PauseMenuActor::setupMenuVisualParameters()
{
	setVisible(false);
	setSize(oxygine::getStage()->getSize());
	setColor(backgroundColor_);

	const oxygine::Vector2 buttonFormatterTopLeft = (oxygine::getStage()->getSize() - buttonFormatter_->getSize()) / 2;
	buttonFormatter_->setPosition(buttonFormatterTopLeft);
	addChild(buttonFormatter_);
}

void PauseMenuActor::addButtons()
{
	buttonFormatter_->AddButton("Continue")
		            ->addEventListener(oxygine::TouchEvent::CLICK, [this](oxygine::Event*) { Toggle(); });
	buttonFormatter_->AddButton("Restart")
					->addEventListener(oxygine::TouchEvent::CLICK, [this](oxygine::Event*) 
	{
		oxygine::Stage::instance = new GameStage(getSize());
		oxygine::DebugActor::show();
	});
	buttonFormatter_->AddButton("Main menu")
		            ->addEventListener(oxygine::TouchEvent::CLICK, [this](oxygine::Event*) 
	{
		oxygine::Stage::instance = new MainMenuStage(getSize());
		oxygine::DebugActor::show();
	});
	buttonFormatter_->AddButton("Exit")
		            ->addEventListener(oxygine::TouchEvent::CLICK, [](oxygine::Event*) { oxygine::core::requestQuit(); });
}

void PauseMenuActor::Toggle()
{
	if (IsShown())
	{
		hide();
	}
	else
	{
		show();
	}
}

bool PauseMenuActor::IsShown() const
{
	return getVisible();
}

void PauseMenuActor::show()
{
	oxygine::getStage()->getClock()->pause();
	setVisible(true);
}

void PauseMenuActor::hide()
{
	oxygine::getStage()->getClock()->resume();
	setVisible(false);
}