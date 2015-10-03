#pragma once
#include <SFML\Graphics\Texture.hpp>
#include <memory>
#include <unordered_map>
#include "Log.h"

namespace TextureManager
{
	sf::Texture& GetTexture(const std::string textureName);
}
