#pragma once
#include "WorldObject.h"

namespace Game
{
	class PaperPlane : public Game::WorldObject
	{
	public:
		sf::Texture planeTex;
		PaperPlane();
		~PaperPlane();
	};
}

