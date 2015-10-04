#pragma once
#include <SFML\Graphics\Texture.hpp>
#include <memory>
#include <unordered_map>
#include "Log.h"

namespace TextureManager
{
	sf::Texture& getTexture(const std::string textureName);
}
