#pragma once
#include <SFML\Graphics.hpp>
#include "WorldObject.h"
#include "Settings.h"
#include <iostream>

namespace Game
{
	class Camera : Game::WorldObject
	{
	public:
		Camera(sf::RenderWindow &w, int vWidth, int vHeight);
		~Camera();

		void drawSprites();
		int getViewportWidth();
		int getViewportHeight();
		void setViewportSize(int vWidth, int vHeight);

	private:
		sf::RenderWindow &window;

		//Viewport width and height in units.
		int viewportWidth, viewportHeight;

		//Allows the size of WorldObjects to be independant from resolution
		float pixelsPerUnitX, pixelsPerUnitY;
	};
}

