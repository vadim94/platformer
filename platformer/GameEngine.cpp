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

void GameEngine::checkGraySquareActorLocation(GreySquareActor* obj)
{
	for (GroundActor* actor: groundActors)
	{
		if ((obj->GetLocation().y.Value() + obj->getSize().y) >= actor->GetLocation().y.Value() &&
			obj->GetLocation().y.Value() <= actor->GetLocation().y.Value() &&
			((actor->GetLocation().x.Value() >= obj->GetLocation().x.Value() &&
			actor->GetLocation().x.Value() <= obj->GetLocation().x.Value() + obj->getSize().x) ||
			(actor->GetLocation().x.Value() + actor->getSize().x >= obj->GetLocation().x.Value() &&
			actor->GetLocation().x.Value() + actor->getSize().x <= obj->GetLocation().x.Value() + obj->getSize().x)))
		{
			Distance x(obj->GetLocation().x.Value());
			Distance y(actor->GetLocation().y.Value() - obj->getSize().y);
			oxygine::VectorT2<Distance> newLocation(x, y);

			obj->SetSpeed(zeroSpeedVector_);
			obj->SetAcceleration(zeroAccelerationVector_);
			obj->SetLocation(newLocation);

			return;
		}
	}
}

GameEngine& GameEngine::getInstance()
{
	static GameEngine instance;
	return instance;
}