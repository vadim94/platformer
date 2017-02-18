#include "PauseMenuActor.h"

#include "core/oxygine.h"
#include "Stage.h"
#include "Clock.h"
#include "TouchEvent.h"
#include "DebugActor.h"

#include "MainMenuStage.h"
#include "GameStage.h"

const oxygine::Color PauseMenuActor::kBackgroundColor = oxygine::Color(255, 0, 0, 100);

PauseMenuActor::PauseMenuActor() : button_formatter_(new ButtonAlignerActor)
{
	AddButtons();
	SetupMenuVisualParameters();
}

void PauseMenuActor::SetupMenuVisualParameters()
{
	setVisible(false);
	setSize(oxygine::getStage()->getSize());
	setColor(kBackgroundColor);

	const oxygine::Vector2 button_formatter_top_left = (oxygine::getStage()->getSize() - button_formatter_->getSize()) / 2;
	button_formatter_->setPosition(button_formatter_top_left);
	addChild(button_formatter_);
}

void PauseMenuActor::AddButtons()
{
	button_formatter_->AddButton("Continue")
		            ->addEventListener(oxygine::TouchEvent::CLICK, [this](oxygine::Event*) { Toggle(); });
	button_formatter_->AddButton("Restart")
					->addEventListener(oxygine::TouchEvent::CLICK, [this](oxygine::Event*) 
	{
		oxygine::Stage::instance = new GameStage(getSize());
		oxygine::DebugActor::show();
	});
	button_formatter_->AddButton("Main menu")
		            ->addEventListener(oxygine::TouchEvent::CLICK, [this](oxygine::Event*) 
	{
		oxygine::Stage::instance = new MainMenuStage(getSize());
		oxygine::DebugActor::show();
	});
	button_formatter_->AddButton("Exit")
		            ->addEventListener(oxygine::TouchEvent::CLICK, [](oxygine::Event*) { oxygine::core::requestQuit(); });
}

void PauseMenuActor::Toggle()
{
	if (IsShown())
	{
		Hide();
	}
	else
	{
		Show();
	}
}

bool PauseMenuActor::IsShown() const
{
	return getVisible();
}

void PauseMenuActor::Show()
{
	oxygine::getStage()->getClock()->pause();
	setVisible(true);
}

void PauseMenuActor::Hide()
{
	oxygine::getStage()->getClock()->resume();
	setVisible(false);
}