#include "MainMenuStage.h"

#include "core/oxygine.h"
#include "DebugActor.h"

#include "GameStage.h"

MainMenuStage::MainMenuStage(const oxygine::Vector2& size) : oxygine::Stage(true)
{
	setSize(size);

	spButtonAlignerActor mainMenuButtons = new ButtonAlignerActor();
	addButtons(mainMenuButtons);
	align(mainMenuButtons);
}

void MainMenuStage::addButtons(spButtonAlignerActor mainMenuButtons)
{
	mainMenuButtons->AddButton("New game")
				   ->addEventListener(oxygine::TouchEvent::CLICK, [this](oxygine::Event*)
	{
		oxygine::Stage::instance = new GameStage(getSize());
		oxygine::DebugActor::show();
	});
	mainMenuButtons->AddButton("Exit")
		           ->addEventListener(oxygine::TouchEvent::CLICK, [](oxygine::Event*) { oxygine::core::requestQuit(); });
}

void MainMenuStage::align(spButtonAlignerActor mainMenuButtons)
{
	const oxygine::Vector2 buttonFormatterTopLeft = (getSize() - mainMenuButtons->getSize()) / 2;
	mainMenuButtons->setPosition(buttonFormatterTopLeft);
	addChild(mainMenuButtons);
}
