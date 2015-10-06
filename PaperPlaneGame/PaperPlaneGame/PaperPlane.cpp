#include "PaperPlane.h"
#include "TextureManager.h"


Game::PaperPlane::PaperPlane()
{
	this->sprite = new sf::Sprite;
	this->sprite->setTexture(TextureManager::getTexture("PaperPlane.png"));
	this->position = sf::Vector3f(1, 1, 0);
	this->size.x = 2;
	this->name = "PaperPlane";
}


Game::PaperPlane::~PaperPlane()
{
}
