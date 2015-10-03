#include "TextureManager.h"

std::unordered_map<std::string, sf::Texture*> loadedTextures;

sf::Texture& TextureManager::GetTexture(const std::string textureName)
{
	if (loadedTextures.count(textureName) == 0) //texture not previously loaded
	{
		loadedTextures[textureName] = new sf::Texture();
		const std::string path = "..\\Assets\\" + textureName;

		if (!loadedTextures[textureName]->loadFromFile(path))
		{
			Log::Error("Failed to load texture from path: " + path);
		}
		else
		{
			Log::Message("Loaded texture: " + path);
		}
	}

	return *loadedTextures[textureName];
}