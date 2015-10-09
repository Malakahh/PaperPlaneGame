#pragma once
#include <SFML\Graphics.hpp>
#include "WorldObject.h"
#include "Settings.h"
#include "Log.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

#define Z_LEVEL std::unordered_map<float, std::vector<Game::WorldObject*>>

namespace Game
{
	class Camera : public Game::WorldObject
	{
	public:
		static Game::Camera Singleton;

		Camera(sf::RenderWindow &w, float vWidth, float vHeight);
		~Camera();

		void drawSprites();
		int getViewportWidth() const;
		int getViewportHeight() const;
		void setViewportSize(int vWidth, int vHeight);

	private:
		sf::RenderWindow &window;

		//Viewport width and height in units.
		float viewportWidth, viewportHeight;

		//Allows the size of WorldObjects to be independant from resolution
		float pixelsPerUnitX, pixelsPerUnitY;

		//Objects to draw this frame
		std::unordered_map<int, Z_LEVEL> worldObjectsToDraw;

		//Returns whether or not the world object is visible in the camera, wnad whether or not it should be drawn.
		bool shouldDrawWorldObject(Game::WorldObject& object);

		//Clears worldObjectsToDraw
		void clearWorldObjectsToDraw();

		//Scales a worldobject to its proper pixel size based on world size
		void scaleWorldObjectToUnit(Game::WorldObject& object);

		//Positions a sprite properly accoring to the viewport
		void positionWorldObject(Game::WorldObject& object);
	};
}

