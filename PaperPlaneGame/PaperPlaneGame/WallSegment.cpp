#include "WallSegment.h"



Game::WallSegment::WallSegment()
{
	this->sprite = new sf::Sprite;
	this->sprite->setTexture(TextureManager::getTexture("Wall.png"));
	this->name = "Wall";
}


Game::WallSegment::~WallSegment()
{
}
