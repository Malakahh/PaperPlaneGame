#include "Camera.h"

Game::Camera::Camera(sf::RenderWindow & w, int vWidth, int vHeight) : window(w)
{
	this->setViewportSize(vWidth, vHeight);
	this->shouldDraw = false;
}

Game::Camera::~Camera()
{
}

void Game::Camera::drawSprites()
{
	//Build worldobjects to draw
	for (auto it = Game::AllWorldObjects.begin(); it != Game::AllWorldObjects.end(); ++it)
	{
		Game::WorldObject obj = *(*it);
		if (this->shouldDrawWorldObject(obj))
		{
			this->scaleWorldObjectToUnit(obj);
			this->worldObjectsToDraw[obj.layer][obj.position.z].push_back(obj);
		}
	}
	
	//Draw objects in correct order
	for (auto layerIt = this->worldObjectsToDraw.cbegin(); layerIt != this->worldObjectsToDraw.cend(); ++layerIt) //Layers
	{
		for (auto zLevelIt = layerIt->second.cbegin(); zLevelIt != layerIt->second.cend(); ++zLevelIt) //Z-levels
		{
			for (auto worldObjectIt = zLevelIt->second.cbegin(); worldObjectIt != zLevelIt->second.cend(); ++worldObjectIt) //All WorldObjects at this z-level
			{
				this->window.draw(worldObjectIt->sprite);
			}
		}
	}

	this->clearWorldObjectsToDraw();
}

void Game::Camera::scaleWorldObjectToUnit(Game::WorldObject & object)
{
	if (!object.isScaled)
	{
		sf::Vector2u moop;
		sf::Vector2u spriteSize = object.sprite.getTexture()->getSize();
		sf::Vector2f spriteScale = sf::Vector2f(
			(this->pixelsPerUnitX * object.size.x) / spriteSize.x,
			(this->pixelsPerUnitY * object.size.y) / spriteSize.y);
		object.sprite.setScale(spriteScale);
		object.isScaled = true;
	}
}

bool Game::Camera::shouldDrawWorldObject(WorldObject & object)
{
	if (object.shouldDraw)
	{
		float cameraHalfWidth = static_cast<float>(this->getViewportWidth()) / 2;
		float cameraHalfHeight = static_cast<float>(this->getViewportHeight()) / 2;

		float objectPosition_Right = object.position.x + object.size.x / 2;
		float objectPosition_Left = object.position.x - object.size.x / 2;
		float objectPosition_Up = object.position.y + object.size.y / 2;
		float objectPosition_Down = object.position.y - object.size.y / 2;

		if (this->position.x - cameraHalfWidth < objectPosition_Right && //Right side of worldobject is within the left side of camera
			this->position.x + cameraHalfWidth > objectPosition_Left && //Left side of worldobject is within the right side of camera
			this->position.y + cameraHalfHeight > objectPosition_Down && //Lower side of worldobject is within the top side of camera
			this->position.y - cameraHalfHeight < objectPosition_Up) //Upper side of worldobject is within the bottom side of camera
		{
			return true;
		}
	}

	return false;
}

void Game::Camera::clearWorldObjectsToDraw()
{
	for (auto it = this->worldObjectsToDraw[LAYER_WORLD].begin(); it != this->worldObjectsToDraw[LAYER_WORLD].end(); ++it)
	{
		it->second.clear();
	}
	for (auto it = this->worldObjectsToDraw[LAYER_UI].begin(); it != this->worldObjectsToDraw[LAYER_UI].end(); ++it)
	{
		it->second.clear();
	}
}

int Game::Camera::getViewportWidth() const
{
	return this->viewportWidth;
}

int Game::Camera::getViewportHeight() const
{
	return this->viewportHeight;
}

void Game::Camera::setViewportSize(int vWidth, int vHeight)
{
	this->viewportWidth = vWidth;
	this->viewportHeight = vHeight;
	this->pixelsPerUnitX = static_cast<float>(Settings::ScreenResolutionX) / this->viewportWidth;
	this->pixelsPerUnitY = static_cast<float>(Settings::ScreenResolutionY) / this->viewportHeight;
}

