#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "Camera.h"
#include "PaperPlane.h"
#include "Log.h"

void initSettings()
{
	Settings::ScreenResolutionX = 1280;
	Settings::ScreenResolutionY = 720;
}

int main()
{
	initSettings();
	sf::RenderWindow window(sf::VideoMode(Settings::ScreenResolutionX, Settings::ScreenResolutionY), "SFML works!");
	Game::Camera camera = Game::Camera(window, 16, 9);

	Game::PaperPlane plane;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
				
		}

		window.clear();
		camera.drawSprites();
		window.display();
	}
	
	return 0;
}