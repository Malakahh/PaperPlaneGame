#include "WorldObject.h"

std::vector<Game::WorldObject*> Game::AllWorldObjects;

Game::WorldObject::WorldObject()
{
	Game::AllWorldObjects.push_back(this);
}


Game::WorldObject::~WorldObject()
{	
	Game::AllWorldObjects.erase(std::remove(Game::AllWorldObjects.begin(), Game::AllWorldObjects.end(), this), Game::AllWorldObjects.end());

	if (sprite != nullptr)
	{
		delete sprite;
	}

	if (font != nullptr)
	{
		delete font;
	}

	if (text != nullptr)
	{
		delete text;
	}
}

void Game::WorldObject::Update(int deltaTime)
{

}