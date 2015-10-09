#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "Camera.h"
#include "PaperPlane.h"
#include "Log.h"
#include "WorldObject.h"
#include "FPS.h"

void initSettings()
{
	Settings::ScreenResolutionX = 1600;
	Settings::ScreenResolutionY = 900;
}

int main()
{
	initSettings();
	sf::RenderWindow window(sf::VideoMode(Settings::ScreenResolutionX, Settings::ScreenResolutionY), "SFML works!");
	Game::Camera camera = Game::Camera(window, 19.2, 10.8);

	//Spawn stuff
	Game::PaperPlane plane;
	Game::FPS fps = Game::FPS(camera);

	sf::Clock clock;
	sf::Time lastFrameTime = clock.getElapsedTime();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
				
		}

		//Call update
		sf::Time time = clock.getElapsedTime();
		for (auto it = Game::AllWorldObjects.cbegin(); it != Game::AllWorldObjects.cend(); ++it)
		{
			(*it)->Update(time.asMilliseconds() - lastFrameTime.asMilliseconds());
		}
		lastFrameTime = time;

		window.clear();
		camera.drawSprites();
		window.display();
	}
	
	return 0;
}
