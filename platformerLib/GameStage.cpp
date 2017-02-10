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
#include "MoveEvent.h"

const Distance GameStage::scrollBuffer_ = pixel * 200;

GameStage::GameStage(const oxygine::Vector2& size) : oxygine::Stage(true)
{
	setSize(size);
	createAndAddSquare();
	createAndAddAllGround();
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
   scroller_.Add(actor.get());
}

void GameStage::createAndAddAllGround()
{
	GameEngine::getInstance().reset();

   createAndAddGround(PhysicalObject::Point(50 * pixel, 500 * pixel));
   createAndAddGround(PhysicalObject::Point(160 * pixel, 550 * pixel));
   createAndAddGround(PhysicalObject::Point(270 * pixel, 500 * pixel));
   createAndAddGround(PhysicalObject::Point(380 * pixel, 550 * pixel));
   createAndAddGround(PhysicalObject::Point(710 * pixel, 500 * pixel));
   createAndAddGround(PhysicalObject::Point(820 * pixel, 550 * pixel));
   createAndAddGround(PhysicalObject::Point(50 * pixel, 50 * pixel));
   createAndAddGround(PhysicalObject::Point(160 * pixel, 100 * pixel));
}

void GameStage::createAndAddGround(const PhysicalObject::Point& point)
{
   spGroundActor groundActor = new GroundActor(point);
   addChild(groundActor);
   scroller_.Add(groundActor.get());
}

void GameStage::createAndAddMenu()
{
	pauseMenu_ = new PauseMenuActor();
	addEventListener(oxygine::KeyEvent::KEY_DOWN, [pauseMenu = pauseMenu_](oxygine::Event* event)
	{
		if (dynamic_cast<oxygine::KeyEvent*>(event)->data->keysym.scancode == SDL_SCANCODE_ESCAPE)
			pauseMenu->Toggle();
	});
	addChild(pauseMenu_);

	endGame_ = new EndGameActor();
	addEventListener(EndGameEvent::EVENT, [endGame = endGame_](oxygine::Event* event)
	{
		endGame->show();
		oxygine::Stage::instance->removeAllEventListeners();
	});
	addChild(endGame_);

   addEventListener(MoveEvent::EVENT, [this](oxygine::Event* event)
   {
      MoveEvent* moveEvent = dynamic_cast<MoveEvent*>(event);
      GameEngine::getInstance().checkGraySquareActorLocation(
         moveEvent->movedObject_, moveEvent->oldPosition_, moveEvent->newPosition_);
      scrollIfNeeded(moveEvent->movedObject_->GetLocation());
   });
   
}

void GameStage::scrollIfNeeded(const PhysicalObject::Point& locationOfActiveObject)
{
   Distance distanceToRightBorder = pixel * getWidth() - locationOfActiveObject.x;
   Distance distanceToLeftBorder = locationOfActiveObject.x;
   Distance moveToLeft = distanceToRightBorder - scrollBuffer_;
   Distance moveToRight = scrollBuffer_ - distanceToLeftBorder;
   if (moveToLeft < 0 * pixel) scroller_.MoveBy(moveToLeft);
   if (moveToRight > 0 * pixel) scroller_.MoveBy(moveToRight);
}

bool GameStage::isPaused()
{
	return pauseMenu_->IsShown();
}

bool GameStage::isEnded()
{
	return endGame_->isShown();
}