#include "GameStage.h"

#include "SDL_events.h"
#include "SDL_main.h"
#include "SDL.h"

#include "core/oxygine.h"
#include "KeyEvent.h"
#include "DebugActor.h"

#include "GroundActor.h"
#include "GreySquareActor.h"
#include "PauseMenuActor.h"

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
		if (isPaused())
			return;

		const PhysicalObject::AccelerationVector horizontalAcceleration(500 * pixelPerSquareSecond, Acceleration(0));
		switch (dynamic_cast<oxygine::KeyEvent*>(event)->data->keysym.scancode)
		{
		case SDL_SCANCODE_LEFT:
			actor->SetAcceleration(actor->GetAcceleration() - horizontalAcceleration);
			break;
		case SDL_SCANCODE_RIGHT:
			actor->SetAcceleration(actor->GetAcceleration() + horizontalAcceleration);
			break;
		case SDL_SCANCODE_SPACE:
			actor->Jump();
			break;
		}
	});
	addChild(actor);
}

void GameStage::createAndAddGround()
{
	spGroundActor groundActor1 = new GroundActor(PhysicalObject::Point(50 * pixel, 500 * pixel));
	spGroundActor groundActor2 = new GroundActor(PhysicalObject::Point(160 * pixel, 500 * pixel));
	spGroundActor groundActor3 = new GroundActor(PhysicalObject::Point(270 * pixel, 500 * pixel));
	spGroundActor groundActor4 = new GroundActor(PhysicalObject::Point(380 * pixel, 500 * pixel));
	spGroundActor groundActor5 = new GroundActor(PhysicalObject::Point(710 * pixel, 500 * pixel));
	spGroundActor groundActor6 = new GroundActor(PhysicalObject::Point(820 * pixel, 500 * pixel));

	addChild(groundActor1);
	addChild(groundActor2);
	addChild(groundActor3);
	addChild(groundActor4);
	addChild(groundActor5);
	addChild(groundActor6);
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
}

bool GameStage::isPaused()
{
	return pauseMenu->IsShown();
}