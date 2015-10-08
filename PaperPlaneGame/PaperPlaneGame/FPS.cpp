#include "FPS.h"

Game::FPS::FPS(Game::Camera& camera)
{
	this->layer = LAYER_UI;

	this->name = "FPS";

	text = new sf::Text;
	font = new sf::Font;

	if (!font->loadFromFile("..\\assets\\arial.ttf"))
	{
		Log::Error("Failed to load texture from path: ..\\assets\\arial.ttf");
	}

	text->setFont(*font);
	text->setString("FPS: ");
	text->setStyle(sf::Text::Bold);
	text->setCharacterSize(24);
	text->setColor(sf::Color::White);

	this->position = sf::Vector3f(
		camera.position.x - camera.getViewportWidth() / 2 + this->size.x / 2,
		camera.position.y - camera.getViewportHeight() / 2,
		0);
}


Game::FPS::~FPS()
{
}

void Game::FPS::Update(int deltaTime)
{
	++frameCount;
	dt += deltaTime;
	inverseUpdateFrequency = (1 / updateFrequency);

	if (dt > inverseUpdateFrequency * 1000)
	{
		framerate = frameCount / inverseUpdateFrequency;
		frameCount = 0;
		dt -= static_cast<int>(inverseUpdateFrequency * 1000);
		text->setString("FPS: " + std::to_string(static_cast<int>(framerate + .5)));
	}
}
