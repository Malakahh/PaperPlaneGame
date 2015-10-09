#pragma once
#include "WorldObject.h"

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

