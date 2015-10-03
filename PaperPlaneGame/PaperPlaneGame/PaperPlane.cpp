#include "PaperPlane.h"



Game::PaperPlane::PaperPlane() : WorldObject()
{
	if (!planeTex.loadFromFile("..\\Assets\\PaperPlane.png"))
	{
		//Error
	}

	this->sprite.setTexture(planeTex);
	this->sprite.setPosition(10, 40);
}


Game::PaperPlane::~PaperPlane()
{
}
