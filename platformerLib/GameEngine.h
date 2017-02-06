#pragma once

#include <vector>
#include "PhysicalObject.h"
#include "GroundActor.h"
#include "GreySquareActor.h"

class GameEngine
{
public:
	static GameEngine& getInstance();
	void registrateGroundActor(GroundActor* obj);
	void checkGraySquareActorLocation(GreySquareActor* obj,
									  const PhysicalObject::Point& oldLocation,
									  const PhysicalObject::Point& newLocation);
	
	void reset();

private:
	GameEngine();

private:
	std::vector<GroundActor*> groundActors;
};