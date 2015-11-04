#include "PaperPlane.h"
#include "TextureManager.h"


Game::PaperPlane::PaperPlane()
{
	this->sprite = new sf::Sprite;
	this->sprite->setTexture(TextureManager::getTexture("PaperPlaneRight.png"));
	this->position = sf::Vector3f(0, 3, 0);

	this->size.x = 2;
	this->name = "PaperPlane";
}


Game::PaperPlane::~PaperPlane()
{
}

void Game::PaperPlane::Update(int deltaTime)
{
	float dt = deltaTime / 1000.0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->sprite->setTexture(TextureManager::getTexture("PaperPlaneLeft.png"));
		this->position += sf::Vector3f(-10 * dt, 0, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->sprite->setTexture(TextureManager::getTexture("PaperPlaneRight.png"));
		this->position += sf::Vector3f(10 * dt, 0, 0);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->position += sf::Vector3f(0, 10 * dt, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->position += sf::Vector3f(0, -10 * dt, 0);
	}
}
