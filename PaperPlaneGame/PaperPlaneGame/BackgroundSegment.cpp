#include "BackgroundSegment.h"



Game::BackgroundSegment::BackgroundSegment()
{
	this->sprite = new sf::Sprite;
	this->sprite->setTexture(TextureManager::getTexture("Background.png"));
	this->name = "BackgroundSegment";
}


Game::BackgroundSegment::~BackgroundSegment()
{
}
