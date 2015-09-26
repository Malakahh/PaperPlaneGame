#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Texture planeTex;
	if (!planeTex.loadFromFile("..\\Assets\\PaperPlane.png"))
	{
		//Error
	}

	sf::Sprite sprite;
	sprite.setTexture(planeTex);
	sprite.setPosition(sf::Vector2f(10, 50)); // absolute position

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
				
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}