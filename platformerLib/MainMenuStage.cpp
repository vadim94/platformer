#include "MainMenuStage.h"

#include "core/oxygine.h"
#include "DebugActor.h"

#include "GameStage.h"

MainMenuStage::MainMenuStage(const oxygine::Vector2& size) : oxygine::Stage(true)
{
	setSize(size);

	spButtonAlignerActor main_menu_buttons = new ButtonAlignerActor();
	AddButtons(main_menu_buttons);
	Align(main_menu_buttons);
}

void MainMenuStage::AddButtons(spButtonAlignerActor main_menu_buttons)
{
	main_menu_buttons->AddButton("New game")
				   ->addEventListener(oxygine::TouchEvent::CLICK, [this](oxygine::Event*)
	{
		oxygine::Stage::instance = new GameStage(getSize());
		oxygine::DebugActor::show();
	});
	main_menu_buttons->AddButton("Exit")
		           ->addEventListener(oxygine::TouchEvent::CLICK, [](oxygine::Event*) { oxygine::core::requestQuit(); });
}

void MainMenuStage::Align(spButtonAlignerActor main_menu_buttons)
{
	const oxygine::Vector2 button_formatter_top_left = (getSize() - main_menu_buttons->getSize()) / 2;
	main_menu_buttons->setPosition(button_formatter_top_left);
	addChild(main_menu_buttons);
}
