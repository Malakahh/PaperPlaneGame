#pragma once
#include <SFML\Graphics.hpp>
#include "WorldObject.h"

namespace Game
{
	class FPS : public Game::WorldObject
	{
	public:
		FPS();
		~FPS();

		void Update(int deltaTime) override;

	private:
		float updateFrequency = 4.0;
		float inverseUpdateFrequency = 0;
		int dt = 0;
		float frameCount = 0;
		float framerate = 0;
	};
}
