#include "PaperPlane.h"
#include "TextureManager.h"


Game::PaperPlane::PaperPlane()
{
	this->sprite.setTexture(TextureManager::getTexture("PaperPlane.png"));
	this->sprite.setPosition(10, 40);
	this->size.x = 2;
}


Game::PaperPlane::~PaperPlane()
{
}
