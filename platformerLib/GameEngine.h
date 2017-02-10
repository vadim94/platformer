#pragma once

#include <vector>
#include "PhysicalObject.h"

class GameEngine
{
public:
	static GameEngine& getInstance();
	void registrateObject(PhysicalObject* obj);
	void checkGraySquareActorLocation(PhysicalObject* obj,
									  const PhysicalObject::Point& oldLocation,
									  const PhysicalObject::Point& newLocation);
	
	void reset();

private:
	GameEngine();

private:
	std::vector<PhysicalObject*> groundActors;
};