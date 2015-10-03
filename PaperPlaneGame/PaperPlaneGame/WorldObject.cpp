#include "WorldObject.h"

std::vector<Game::WorldObject*> Game::AllWorldObjects;

Game::WorldObject::WorldObject()
{
	Game::AllWorldObjects.push_back(this);
}


Game::WorldObject::~WorldObject()
{
}
