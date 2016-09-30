#pragma once

#include <vector>
#include "GroundActor.h"
#include "GreySquareActor.h"

class GameEngine
{
public:
	static GameEngine& getInstance();
	void registrateGroundActor(GroundActor* obj);
	void checkGraySquareActorLocation(GreySquareActor* obj);

private:
	GameEngine();

private:
	std::vector<GroundActor*> groundActors;
};