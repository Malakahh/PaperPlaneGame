#include "PaperPlane.h"
#include "TextureManager.h"


Game::PaperPlane::PaperPlane() : WorldObject()
{
	this->sprite.setTexture(TextureManager::GetTexture("PaperPlane.png"));
	this->sprite.setPosition(10, 40);
}


Game::PaperPlane::~PaperPlane()
{
}
