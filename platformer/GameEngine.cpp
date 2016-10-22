#include "GameEngine.h"

PhysicalObject::SpeedVector zeroSpeedVector_ { Speed(0), Speed(0) };
PhysicalObject::AccelerationVector zeroAccelerationVector_ { Acceleration(0), Acceleration(0) };

GameEngine::GameEngine()
{
}

void GameEngine::registrateGroundActor(GroundActor* actor)
{
	groundActors.push_back(actor);
}

enum DIRECTION
{
	NOT_CHANGED,
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT
};

void GameEngine::checkGraySquareActorLocation(GreySquareActor* actor,
											  const PhysicalObject::Point& oldLocation,
											  const PhysicalObject::Point& newLocation)
{
	DIRECTION direction;
	if (oldLocation.x.Value() < newLocation.x.Value()) {
		if (oldLocation.y.Value() < newLocation.y.Value()) {
			direction = DOWN_RIGHT;
		} else if (oldLocation.y.Value() > newLocation.y.Value()) {
			direction = UP_RIGHT;
		} else {
			direction = RIGHT;
		}
	}
	else if (oldLocation.x.Value() > newLocation.x.Value()) {
		if (oldLocation.y.Value() < newLocation.y.Value()) {
			direction = DOWN_LEFT;
		} else if (oldLocation.y.Value() > newLocation.y.Value()) {
			direction = UP_LEFT;
		} else {
			direction = LEFT;
		}
	} else {
		if (oldLocation.y.Value() < newLocation.y.Value()) {
			direction = DOWN;
		} else if (oldLocation.y.Value() > newLocation.y.Value()) {
			direction = UP;
		} else {
			direction = NOT_CHANGED;
			return;
		}
	}

	Distance newX(actor->GetLocation().x.Value()), newY(actor->GetLocation().y.Value());
	bool isTouched = false;

	double yActorOldUpperBound = oldLocation.y.Value();
	double yActorNewUpperBound = newLocation.y.Value();
	double yActorOldLowerBound = oldLocation.y.Value() + actor->getSize().y;
	double yActorNewLowerBound = newLocation.y.Value() + actor->getSize().y;
	double xActorLeftBound = newLocation.x.Value();
	double xActorRightBound = newLocation.x.Value() + actor->getSize().x;
	double xActorOldLeftBound = oldLocation.x.Value();
	double xActorOldRightBound = oldLocation.x.Value() + actor->getSize().x;

	for (GroundActor* barrier: groundActors)
	{
		double xBarrierRightBound = barrier->GetLocation().x.Value() + barrier->getSize().x;
		double xBarrierLeftBound = barrier->GetLocation().x.Value();
		double yBarrierUpperBound = barrier->GetLocation().y.Value();
		double yBarrierLowerBound = barrier->GetLocation().y.Value() + barrier->getSize().y;

		// Set Y value
		switch (direction)
		{
		case UP_RIGHT:
		case UP_LEFT:
		case UP:
			if (yBarrierLowerBound > yActorNewUpperBound &&
				yBarrierLowerBound <= yActorOldUpperBound &&
				((xActorLeftBound >= xBarrierLeftBound &&
				xActorLeftBound <= xBarrierRightBound) ||
				(xActorRightBound <= xBarrierRightBound &&
				xActorRightBound >= xBarrierLeftBound)))
			{
				isTouched = true;
				if (newY.Value() < yBarrierLowerBound)
				{
					newY.Value() = yBarrierLowerBound;
				}
			}
			break;
		case DOWN_LEFT:
		case DOWN_RIGHT:
		case DOWN:
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
				if (newY.Value() > yBarrierUpperBound - actor->getSize().y)
				{
					newY.Value() = yBarrierUpperBound - actor->getSize().y;
				}
			}
			break;
		}

		// Set X value
		switch (direction)
		{
		case DOWN_RIGHT:
		case UP_RIGHT:
		case RIGHT:
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
				if (newX.Value() > (xBarrierLeftBound - actor->getSize().x))
				{
					newX.Value() = xBarrierLeftBound - actor->getSize().x;
				}
			}
			break;
		case UP_LEFT:
		case DOWN_LEFT:
		case LEFT:
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
				if (newX.Value() < xBarrierRightBound)
				{
					newX.Value() = xBarrierRightBound;
				}
			}
			break;
		}
	}

	if (isTouched) {
		oxygine::VectorT2<Distance> newLocation(newX, newY);
		actor->SetLocation(newLocation);
		actor->SetSpeed(zeroSpeedVector_);
		actor->SetAcceleration(zeroAccelerationVector_);
	}

	return;
}

GameEngine& GameEngine::getInstance()
{
	static GameEngine instance;
	return instance;
}