#include "ControlObject.h"

std::vector<Game::ControlObject*> Game::AllControlObjects;

Game::ControlObject::ControlObject()
{
	Game::AllControlObjects.push_back(this);
}


Game::ControlObject::~ControlObject()
{
}

void Game::ControlObject::Update(int deltaTime)
{

}