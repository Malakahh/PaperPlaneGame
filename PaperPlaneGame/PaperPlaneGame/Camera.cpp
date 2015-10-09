#include "Camera.h"

#define CAMERA_HALF_WIDTH this->getViewportWidth() / 2.0f
#define CAMERA_HALF_HEIGHT this->getViewportHeight() / 2.0f

Game::Camera::Camera(sf::RenderWindow & w, float vWidth, float vHeight) : window(w)
{
	this->setViewportSize(vWidth, vHeight);
	this->shouldDraw = false;
	this->name = "Camera";
}

Game::Camera::~Camera()
{
}

void Game::Camera::drawSprites()
{
	//Build worldobjects to draw
	for (auto it = Game::AllWorldObjects.cbegin(); it != Game::AllWorldObjects.cend(); ++it)
	{
		Game::WorldObject* obj = *it;
		if (this->shouldDrawWorldObject(*obj))
		{
			this->scaleWorldObjectToUnit(*obj);
			this->positionWorldObject(*obj);
			this->worldObjectsToDraw[obj->layer][obj->position.z].push_back(obj);
		}
	}
	
	//Draw objects in correct order
	for (auto layerIt = this->worldObjectsToDraw.cbegin(); layerIt != this->worldObjectsToDraw.cend(); ++layerIt) //Layers
	{
		for (auto zLevelIt = layerIt->second.cbegin(); zLevelIt != layerIt->second.cend(); ++zLevelIt) //Z-levels
		{
			for (auto worldObjectIt = zLevelIt->second.cbegin(); worldObjectIt != zLevelIt->second.cend(); ++worldObjectIt) //All WorldObjects at this z-level
			{
				Game::WorldObject* obj = *worldObjectIt;

				if (obj->sprite != nullptr)
				{
					this->window.draw(*obj->sprite);
				}
	
				if (obj->text != nullptr)
				{
					this->window.draw(*obj->text);
				}
			}
		}
	}

	this->clearWorldObjectsToDraw();
}

void Game::Camera::scaleWorldObjectToUnit(Game::WorldObject & object)
{
	if (!object.isScaled && object.sprite != nullptr)
	{
		sf::Vector2u moop;
		sf::Vector2u spriteSize = object.sprite->getTexture()->getSize();
		sf::Vector2f spriteScale = sf::Vector2f(
			(this->pixelsPerUnitX * object.size.x) / spriteSize.x,
			(this->pixelsPerUnitY * object.size.y) / spriteSize.y);
		object.sprite->setScale(spriteScale);
		object.isScaled = true;
	}
}

void Game::Camera::positionWorldObject(Game::WorldObject & object)
{
	float x = (this->position.x + object.position.x - object.size.x / 2 + CAMERA_HALF_WIDTH) * pixelsPerUnitX;
	float y = (this->position.y - object.position.y - object.size.y / 2 + CAMERA_HALF_HEIGHT) * pixelsPerUnitY;

	if (object.sprite != nullptr)
	{
		object.sprite->setPosition(sf::Vector2f(x, y));
	}

	if (object.text != nullptr)
	{
		object.text->setPosition(sf::Vector2f(x, y));
	}
}

bool Game::Camera::shouldDrawWorldObject(WorldObject & object)
{
	if (object.shouldDraw)
	{
		float objectPosition_Right = object.position.x + object.size.x / 2.0f;
		float objectPosition_Left = object.position.x - object.size.x / 2.0f;
		float objectPosition_Up = object.position.y + object.size.y / 2.0f;
		float objectPosition_Down = object.position.y - object.size.y / 2.0f;

		if (this->position.x - CAMERA_HALF_WIDTH < objectPosition_Right && //Right side of worldobject is within the left side of camera
			this->position.x + CAMERA_HALF_WIDTH > objectPosition_Left && //Left side of worldobject is within the right side of camera
			this->position.y - CAMERA_HALF_HEIGHT < objectPosition_Up && //Upper side of worldobject is within the bottom side of camera
			this->position.y + CAMERA_HALF_HEIGHT > objectPosition_Down) //Lower side of worldobject is within the top side of camera
		{
			return true;
		}
	}

	if (object.name == "PaperPlane")
	{
		Log::Message("Shouldn't draw");
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

float Game::Camera::getViewportWidth() const
{
	return this->viewportWidth;
}

float Game::Camera::getViewportHeight() const
{
	return this->viewportHeight;
}

void Game::Camera::setViewportSize(float vWidth, float vHeight)
{
	this->viewportWidth = vWidth;
	this->viewportHeight = vHeight;
	this->pixelsPerUnitX = static_cast<float>(Settings::ScreenResolutionX) / this->viewportWidth;
	this->pixelsPerUnitY = static_cast<float>(Settings::ScreenResolutionY) / this->viewportHeight;
}

