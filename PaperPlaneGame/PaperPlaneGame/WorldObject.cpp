#include "WorldObject.h"

std::vector<Game::WorldObject*> Game::AllWorldObjects;

Game::WorldObject::WorldObject()
{
	Game::AllWorldObjects.push_back(this);
}


Game::WorldObject::~WorldObject()
{
	Log::Error(this->name + " destructor called");
	
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