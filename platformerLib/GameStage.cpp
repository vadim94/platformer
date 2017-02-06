#include "GameStage.h"
#include "GameEngine.h"

#include "SDL_events.h"
#include "SDL_main.h"
#include "SDL.h"

#include "core/oxygine.h"
#include "KeyEvent.h"
#include "DebugActor.h"

#include "GroundActor.h"
#include "GreySquareActor.h"
#include "PauseMenuActor.h"
#include "Direction.h"

#include "EndGameEvent.h"

GameStage::GameStage(const oxygine::Vector2& size) : oxygine::Stage(true)
{
	setSize(size);
	createAndAddSquare();
	createAndAddGround();
	createAndAddMenu();
}

void GameStage::createAndAddSquare()
{
	spGreySquareActor actor = new GreySquareActor(PhysicalObject::Point(50 * pixel, 50 * pixel));
	addEventListener(oxygine::KeyEvent::KEY_DOWN, [this, actor](oxygine::Event* event)
	{
		if (isPaused() || isEnded())
			return;

		switch (dynamic_cast<oxygine::KeyEvent*>(event)->data->keysym.scancode)
		{
		case SDL_SCANCODE_LEFT:
			actor->MoveHorizontally(Direction::Left);
			break;
		case SDL_SCANCODE_RIGHT:
			actor->MoveHorizontally(Direction::Right);
			break;
		case SDL_SCANCODE_SPACE:
			actor->Jump();
			break;
		}
	});

   addEventListener(oxygine::KeyEvent::KEY_UP, [this, actor](oxygine::Event* event)
   {
      const auto scancode = dynamic_cast<oxygine::KeyEvent*>(event)->data->keysym.scancode;
      if (scancode == SDL_SCANCODE_LEFT || scancode == SDL_SCANCODE_RIGHT)
      {
         actor->StopMoveHorizontally();
      }
   });

	addChild(actor);
}

void GameStage::createAndAddGround()
{
	GameEngine::getInstance().reset();

	spGroundActor groundActor1 = new GroundActor(PhysicalObject::Point(50 * pixel, 500 * pixel));
	spGroundActor groundActor2 = new GroundActor(PhysicalObject::Point(160 * pixel, 550 * pixel));
	spGroundActor groundActor3 = new GroundActor(PhysicalObject::Point(270 * pixel, 500 * pixel));
	spGroundActor groundActor4 = new GroundActor(PhysicalObject::Point(380 * pixel, 550 * pixel));
	spGroundActor groundActor5 = new GroundActor(PhysicalObject::Point(710 * pixel, 500 * pixel));
	spGroundActor groundActor6 = new GroundActor(PhysicalObject::Point(820 * pixel, 550 * pixel));
	spGroundActor groundActor7 = new GroundActor(PhysicalObject::Point(50 * pixel, 50 * pixel));
	spGroundActor groundActor8 = new GroundActor(PhysicalObject::Point(160 * pixel, 100 * pixel));

	addChild(groundActor1);
	addChild(groundActor2);
	addChild(groundActor3);
	addChild(groundActor4);
	addChild(groundActor5);
	addChild(groundActor6);
	addChild(groundActor7);
	addChild(groundActor8);
}

void GameStage::createAndAddMenu()
{
	pauseMenu = new PauseMenuActor();
	addEventListener(oxygine::KeyEvent::KEY_DOWN, [pauseMenu = pauseMenu](oxygine::Event* event)
	{
		if (dynamic_cast<oxygine::KeyEvent*>(event)->data->keysym.scancode == SDL_SCANCODE_ESCAPE)
			pauseMenu->Toggle();
	});
	addChild(pauseMenu);

	endGame = new EndGameActor();
	addEventListener(EndGameEvent::EVENT, [endGame = endGame](oxygine::Event* event)
	{
		endGame->show();
		oxygine::Stage::instance->removeAllEventListeners();
	});
	addChild(endGame);
}

bool GameStage::isPaused()
{
	return pauseMenu->IsShown();
}

bool GameStage::isEnded()
{
	return endGame->isShown();
}