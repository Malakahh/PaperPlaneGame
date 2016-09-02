#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "Camera.h"
#include "PaperPlane.h"
#include "Log.h"
#include "WorldObject.h"
#include "FPS.h"
#include "LevelGenerator.h"

void initSettings()
{
	Settings::ScreenResolutionX = 1600;
	Settings::ScreenResolutionY = 900;
}

int main()
{
	initSettings();
	sf::RenderWindow window(sf::VideoMode(Settings::ScreenResolutionX, Settings::ScreenResolutionY), "SFML works!");
	Game::Camera camera = Game::Camera(window, 19.2f, 10.8f);

	//Spawn stuff
	Game::PaperPlane plane;
	Game::FPS fps = Game::FPS(camera);
	Game::LevelGenerator levelGen = Game::LevelGenerator(camera);

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

		sf::Time time = clock.getElapsedTime();

		//Call WorldObject update
		for (auto it = Game::AllWorldObjects.cbegin(); it != Game::AllWorldObjects.cend(); ++it)
		{
			(*it)->Update(time.asMilliseconds() - lastFrameTime.asMilliseconds());
		}
		

		//Call ControlObject update
		for (auto it = Game::AllControlObjects.cbegin(); it != Game::AllControlObjects.cend(); ++it)
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
