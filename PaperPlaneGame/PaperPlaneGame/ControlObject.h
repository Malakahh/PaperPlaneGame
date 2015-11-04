#pragma once
#include <vector>

namespace Game
{

	/*	Similar to WorldObjects, but with a distinction.
	ControlObjects have no position in the world and does not need one.
	ControlObjects are guaranteed to recieve their events before WorldObjects.
	ControlObjects should be used for things like game managers, level generators, etc. Anything that needs to respond to ingame events, but is not directly part of the game world.*/
	class ControlObject
	{
	public:
		ControlObject();
		~ControlObject();

		//Called every frame, deltaTime is in ms
		virtual void Update(int deltaTime);
	};

	extern std::vector<Game::ControlObject*> AllControlObjects;
}
