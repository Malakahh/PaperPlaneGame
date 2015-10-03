#include "Camera.h"

Game::Camera::Camera(sf::RenderWindow & w, int vWidth, int vHeight) : window(w)
{
	this->setViewportSize(vWidth, vHeight);
}

Game::Camera::~Camera()
{
}

void Game::Camera::drawSprites()
{
	for (auto it = Game::AllWorldObjects.cbegin(); it != Game::AllWorldObjects.cend(); ++it)
	{
		this->window.draw((*it)->sprite);
	}
}

int Game::Camera::getViewportWidth()
{
	return this->viewportWidth;
}

int Game::Camera::getViewportHeight()
{
	return this->viewportHeight;
}

void Game::Camera::setViewportSize(int vWidth, int vHeight)
{
	this->viewportWidth = vWidth;
	this->viewportHeight = vHeight;
	this->pixelsPerUnitX = static_cast<float>(Settings::ScreenResolutionX) / this->viewportWidth;
	this->pixelsPerUnitY = static_cast<float>(Settings::ScreenResolutionY) / this->viewportHeight;
}
