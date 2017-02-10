#include "GameEngine.h"
#include "Direction.h"

#include "EndGameEvent.h"
#include "Stage.h"

PhysicalObject::SpeedVector zeroSpeedVector_ { Speed(0), Speed(0) };
PhysicalObject::AccelerationVector zeroAccelerationVector_ { Acceleration(0), Acceleration(0) };

GameEngine::GameEngine()
{
}

void GameEngine::registrateObject(PhysicalObject* actor)
{
	groundActors.push_back(actor);
}

void GameEngine::checkGraySquareActorLocation(PhysicalObject* actor,
											  const PhysicalObject::Point& oldLocation,
											  const PhysicalObject::Point& newLocation)
{
	Direction horisontalDirection = Direction::NotChanged;
	Direction verticalDirection = Direction::NotChanged;
	
	// Check end game (fall)
	if ((newLocation.y + actor->GetSize().y) >= oxygine::getStage()->getSize().y * pixel)
	{
		EndGameEvent ev;
		oxygine::Stage::instance->dispatchEvent(&ev);
	}

	if (oldLocation.x < newLocation.x) {
		horisontalDirection = Direction::Right;
	}
	else if (oldLocation.x > newLocation.x) {
		horisontalDirection = Direction::Left;
	}

	if (oldLocation.y < newLocation.y) {
		verticalDirection = Direction::Down;
	}
	else if (oldLocation.y > newLocation.y) {
		verticalDirection = Direction::Up;
	}

	Distance newX(actor->GetLocation().x.Value()), newY(actor->GetLocation().y.Value());
	bool isTouched = false;

	Distance yActorOldUpperBound = oldLocation.y;
   Distance yActorNewUpperBound = newLocation.y;
   Distance yActorOldLowerBound = oldLocation.y + actor->GetSize().y;
   Distance yActorNewLowerBound = newLocation.y + actor->GetSize().y;
   Distance xActorLeftBound = newLocation.x;
   Distance xActorRightBound = newLocation.x + actor->GetSize().x;
   Distance xActorOldLeftBound = oldLocation.x;
   Distance xActorOldRightBound = oldLocation.x + actor->GetSize().x;

	for (PhysicalObject* barrier: groundActors)
	{
      Distance xBarrierRightBound = barrier->GetLocation().x + barrier->GetSize().x;
      Distance xBarrierLeftBound = barrier->GetLocation().x;
      Distance yBarrierUpperBound = barrier->GetLocation().y;
      Distance yBarrierLowerBound = barrier->GetLocation().y + barrier->GetSize().y;

		// Set Y value
		switch (verticalDirection)
		{
		case Direction::Up:
			if (yBarrierLowerBound > yActorNewUpperBound &&
				yBarrierLowerBound <= yActorOldUpperBound &&
				((xActorLeftBound >= xBarrierLeftBound &&
				xActorLeftBound <= xBarrierRightBound) ||
				(xActorRightBound <= xBarrierRightBound &&
				xActorRightBound >= xBarrierLeftBound)))
			{
				isTouched = true;
				if (newY < yBarrierLowerBound)
				{
					newY = yBarrierLowerBound;
				}
			}
			break;
		case Direction::Down:
			if (yBarrierUpperBound < yActorNewLowerBound &&
				yBarrierUpperBound >= yActorOldLowerBound &&
				((xActorLeftBound >= xBarrierLeftBound &&
			    xActorLeftBound <= xBarrierRightBound) ||
				(xActorRightBound <= xBarrierRightBound &&
				xActorRightBound >= xBarrierLeftBound) || 
				(xActorLeftBound < xBarrierLeftBound &&
				xActorRightBound > xBarrierRightBound)))
			{
				isTouched = true;
				if (newY > yBarrierUpperBound - actor->GetSize().y)
				{
					newY = yBarrierUpperBound - actor->GetSize().y;
				}
			}
			break;
		}

		// Set X value
		switch (horisontalDirection)
		{
		case Direction::Right:
			if (xBarrierLeftBound < xActorRightBound &&
				xBarrierLeftBound >= xActorOldRightBound &&
				((yActorNewUpperBound >= yBarrierUpperBound &&
				yActorNewUpperBound <= yBarrierLowerBound) ||
				(yActorNewLowerBound >= yBarrierUpperBound &&
				yActorNewLowerBound <= yBarrierLowerBound) ||
				(yActorNewUpperBound < yBarrierUpperBound &&
				yActorNewLowerBound > yBarrierLowerBound)))
			{
				isTouched = true;
				if (newX > (xBarrierLeftBound - actor->GetSize().x))
				{
					newX = xBarrierLeftBound - actor->GetSize().x;
				}
			}
			break;
		case Direction::Left:
			if (xBarrierRightBound > xActorLeftBound &&
				xBarrierRightBound <= xActorOldLeftBound &&
				((yActorNewUpperBound >= yBarrierUpperBound &&
				yActorNewUpperBound <= yBarrierLowerBound) ||
				(yActorNewLowerBound >= yBarrierUpperBound &&
				yActorNewLowerBound <= yBarrierLowerBound) ||
				(yActorNewUpperBound < yBarrierUpperBound &&
				yActorNewLowerBound > yBarrierLowerBound)))
			{
				isTouched = true;
				if (newX < xBarrierRightBound)
				{
					newX = xBarrierRightBound;
				}
			}
			break;
		}
	}

	if (isTouched)
	{
		PhysicalObject::Point newLocation(newX, newY);
		actor->SetLocation(newLocation);
		actor->SetSpeed(zeroSpeedVector_);
		actor->SetAcceleration(zeroAccelerationVector_);
	}

	return;
}

void GameEngine::reset()
{
	groundActors.clear();
}

GameEngine& GameEngine::getInstance()
{
	static GameEngine instance;
	return instance;
}