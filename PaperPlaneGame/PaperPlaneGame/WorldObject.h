#pragma once
#include <SFML\System\Vector3.hpp>
#include <SFML\Graphics.hpp>
#include "Log.h"
#include <vector>
#include <memory>

#define LAYER_WORLD 0
#define LAYER_UI 1

namespace Game
{
	/*	Similar to Unitys GameObjects, but with a distinction.
		WorldObjects has and indeed has a use for their position in the world.
		This would be true for most GameObjects in Unity as well, but an instance where this isn't the case, would be when creating managers that needs the evens from MonoBehavior.*/
	class WorldObject
	{
	public:
		//World position in units
		sf::Vector3f position = sf::Vector3f(0,0,0);

		//Size in units
		sf::Vector2f size = sf::Vector2f(1, 1);

		//Layer in which to draw this WorldObject
		int layer = LAYER_WORLD;

		//Sprite
		sf::Sprite *sprite;

		//Text
		sf::Font *font;
		sf::Text *text;

		//Determines whether or not the object needs to be scaled
		bool isScaled = false;

		bool shouldDraw = true;

		std::string name = "WorldObject";

		WorldObject();
		~WorldObject();

		//Called every frame, deltaTime is in ms
		virtual void Update(int deltaTime);
	};

	extern std::vector<Game::WorldObject*> AllWorldObjects;
}
