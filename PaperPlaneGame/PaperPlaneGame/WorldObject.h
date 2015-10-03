#pragma once
#include <SFML\System\Vector3.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>


namespace Game
{
	/*	Similar to Unitys GameObjects, but with a distinction.
		WorldObjects has and indeed has a use for their position in the world.
		This would be true for most GameObjects in Unity as well, but an instance where this isn't the case, would be when creating managers that needs the evens from MonoBehavior.*/
	class WorldObject
	{
	public:

		sf::Vector3f position = sf::Vector3f(0,0,0);
		sf::Vector2f size = sf::Vector2f(1, 1);
		sf::Sprite sprite;

		WorldObject();
		~WorldObject();
	};

	extern std::vector<Game::WorldObject*> AllWorldObjects;
}
