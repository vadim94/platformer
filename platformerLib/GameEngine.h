#pragma once

#include <vector>
#include "PhysicalObject.h"

class GameEngine
{
public:
	static GameEngine& GetInstance();
	void RegistrateObject(PhysicalObject* obj);
	void CheckGraySquareActorLocation(PhysicalObject* obj,
									  const PhysicalObject::Point& old_location,
									  const PhysicalObject::Point& new_location);
	
	void Reset();

private:
	GameEngine();

private:
	std::vector<PhysicalObject*> ground_actors_;
};