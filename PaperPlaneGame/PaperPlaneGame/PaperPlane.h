#pragma once
#include "WorldObject.h"
#include "TextureManager.h"
#include <functional>

namespace Game
{
	class PaperPlane : public Game::WorldObject
	{
	public:
		PaperPlane();
		~PaperPlane();

		void Update(int deltaTime) override;
	};
}

