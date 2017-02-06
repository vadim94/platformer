#include "EndGameActor.h"
#include "GameStage.h"
#include "MainMenuStage.h"

#include "Stage.h"
#include "Clock.h"
#include "core/oxygine.h"
#include "DebugActor.h"

const oxygine::Color EndGameActor::backgroundColor_ = oxygine::Color(255, 0, 0, 100);

EndGameActor::EndGameActor()
{
	setVisible(false);
	setSize(oxygine::getStage()->getSize());
	setColor(backgroundColor_);

	spButtonAlignerActor endGameStageButtons = new ButtonAlignerActor();
	addButtons(endGameStageButtons);
	align(endGameStageButtons);
}

void EndGameActor::addButtons(spButtonAlignerActor endGameStageButtons)
{
	endGameStageButtons->AddButton("Restart")
		->addEventListener(oxygine::TouchEvent::CLICK, [this](oxygine::Event*)
	{
		oxygine::Stage::instance = new GameStage(getSize());
		oxygine::DebugActor::show();
	});
	endGameStageButtons->AddButton("Main menu")
		->addEventListener(oxygine::TouchEvent::CLICK, [](oxygine::Event*)
	{ 
		oxygine::Stage::instance = new MainMenuStage(oxygine::core::getDisplaySize());
		oxygine::DebugActor::show();
	});
}

void EndGameActor::align(spButtonAlignerActor endGameStageButtons)
{
	const oxygine::Vector2 buttonFormatterTopLeft = (getSize() - endGameStageButtons->getSize()) / 2;
	endGameStageButtons->setPosition(buttonFormatterTopLeft);
	addChild(endGameStageButtons);
}

void EndGameActor::show()
{
	oxygine::getStage()->getClock()->pause();
	setVisible(true);
}

bool EndGameActor::isShown() const
{
	return getVisible();
}