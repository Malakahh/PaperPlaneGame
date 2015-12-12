#include "EventSystem.h"
	
//Using unordered_map for faster single read, and map for faster range read
std::unordered_map<short, std::map<Game::WorldObject*, void*>> EventSystem::worldObjectCallbacks;
std::unordered_map<short, std::map<Game::ControlObject*, void*>> EventSystem::controlObjectCallbacks;

#ifdef _DEBUG
bool callback()
{
	return true;
}

void Test_RegisterEventWorldObject()
{
	static bool hasRun = false;
	if (!hasRun)
	{
		hasRun = true;

		Game::WorldObject obj;

		//Testing event == SHRT_MIN
		EventSystem::RegisterEvent(SHRT_MIN, callback, &obj);
		assert(EventSystem::worldObjectCallbacks.count(SHRT_MIN) == 0);

		//Testing event == -1
		EventSystem::RegisterEvent(-1, callback, &obj);
		assert(EventSystem::worldObjectCallbacks.count(-1) == 0);

		//Testing event == 0
		EventSystem::RegisterEvent(0, callback, &obj);
		assert(EventSystem::worldObjectCallbacks.count(0) == 0);

		//Testing event == 1
		EventSystem::RegisterEvent(1, callback, &obj);
		assert(EventSystem::worldObjectCallbacks.count(1));
		auto map1 = EventSystem::worldObjectCallbacks.find(1)->second;
		assert(map1.count(&obj));
		auto cb1 = EventSystem::GetTargetedEventCallback<bool()>(1, &obj);
		assert(cb1());
		EventSystem::worldObjectCallbacks.erase(1);
		assert(EventSystem::worldObjectCallbacks.count(1) == 0);

		//Testing event == SHRT_MAX
		EventSystem::RegisterEvent(SHRT_MAX, callback, &obj);
		assert(EventSystem::worldObjectCallbacks.count(SHRT_MAX));
		auto mapSHRT_MAX = EventSystem::worldObjectCallbacks.find(SHRT_MAX)->second;
		assert(mapSHRT_MAX.count(&obj));
		auto cbSHRT_MAX = EventSystem::GetTargetedEventCallback<bool()>(SHRT_MAX, &obj);
		assert(cbSHRT_MAX());
		EventSystem::worldObjectCallbacks.erase(SHRT_MAX);
		assert(EventSystem::worldObjectCallbacks.count(SHRT_MAX) == 0);
	}
}

void Test_RegisterEventControlObject()
{
	static bool hasRun = false;
	if (!hasRun)
	{
		hasRun = true;

		Game::ControlObject obj;

		//Testing event == SHRT_MIN
		EventSystem::RegisterEvent(SHRT_MIN, callback, &obj);
		assert(EventSystem::controlObjectCallbacks.count(SHRT_MIN));
		auto mapSHRT_MIN = EventSystem::controlObjectCallbacks.find(SHRT_MIN)->second;
		assert(mapSHRT_MIN.count(&obj));
		auto cbSHRT_MIN = EventSystem::GetTargetedEventCallback<bool()>(SHRT_MIN, &obj);
		assert(cbSHRT_MIN());
		EventSystem::worldObjectCallbacks.erase(SHRT_MIN);
		assert(EventSystem::worldObjectCallbacks.count(SHRT_MIN) == 0);

		//Testing event == -1
		EventSystem::RegisterEvent(-1, callback, &obj);
		assert(EventSystem::controlObjectCallbacks.count(-1));
		auto map1 = EventSystem::controlObjectCallbacks.find(-1)->second;
		assert(map1.count(&obj));
		auto cb1 = EventSystem::GetTargetedEventCallback<bool()>(-1, &obj);
		assert(cb1());
		EventSystem::worldObjectCallbacks.erase(-1);
		assert(EventSystem::worldObjectCallbacks.count(-1) == 0);

		//Testing event == 0
		EventSystem::RegisterEvent(0, callback, &obj);
		assert(EventSystem::controlObjectCallbacks.count(0) == 0);

		//Testing event == 1
		EventSystem::RegisterEvent(1, callback, &obj);
		assert(EventSystem::controlObjectCallbacks.count(1) == 0);

		//Testing event == SHRT_MAX
		EventSystem::RegisterEvent(SHRT_MAX, callback, &obj);
		assert(EventSystem::controlObjectCallbacks.count(SHRT_MAX) == 0);
	}
}
#endif

bool EventSystem::RegisterEvent(short eventID, void* callback, Game::WorldObject* obj)
{
	#ifdef _DEBUG
		Test_RegisterEventWorldObject();
	#endif

	//Check if using proper event for this object
	if (eventID <= 0)
	{
		return false;
	}

	//Make sure map exists
	if (EventSystem::worldObjectCallbacks.count(eventID) <= 0)
	{
		std::map<Game::WorldObject*, void*> map;
		std::pair<short, std::map<Game::WorldObject*, void*>> mapPair(eventID, map);
		EventSystem::worldObjectCallbacks.insert(mapPair);
	}

	//Insert pair
	std::pair<Game::WorldObject*, void*> pair(obj, callback);
	EventSystem::worldObjectCallbacks.find(eventID)->second.insert(pair);

	return true;
}

bool EventSystem::RegisterEvent(short eventID, void* callback, Game::ControlObject* obj)
{
	#ifdef _DEBUG
		Test_RegisterEventControlObject();
	#endif

	//Check if using proper event for this object
	if (eventID >= 0)
	{
		return false;
	}

	//Make sure map exists
	if (EventSystem::controlObjectCallbacks.count(eventID) <= 0)
	{
		std::map<Game::ControlObject*, void*> map;
		std::pair<short, std::map<Game::ControlObject*, void*>> mapPair(eventID, map);
		EventSystem::controlObjectCallbacks.insert(mapPair);
	}

	//Insert pair
	std::pair<Game::ControlObject*, void*> pair(obj, callback);
	EventSystem::controlObjectCallbacks.find(eventID)->second.insert(pair);

	return true;
}

#ifdef _DEBUG
void Test_UnregisterEventWorldObject()
{
	static bool hasRun = false;
	if (!hasRun)
	{
		Game::WorldObject obj;
		EventSystem::RegisterEvent(1, callback, &obj);

		//Event == -1
		assert(EventSystem::UnregisterEvent(-1, &obj) == false);
		
		//Event == SHRT_MIN
		assert(EventSystem::UnregisterEvent(SHRT_MIN, &obj) == false);

		//Event == 2 (one that doesn't exist, but is valid)
		assert(EventSystem::UnregisterEvent(2, &obj) == false);

		//Event == 1
		assert(EventSystem::UnregisterEvent(1, &obj));
		assert(EventSystem::worldObjectCallbacks.empty());
	}
}

void Test_UnregisterEventControlObject()
{
	static bool hasRun = false;
	if (!hasRun)
	{
		Game::ControlObject obj;
		EventSystem::RegisterEvent(-1, callback, &obj);

		//Event == 1
		assert(EventSystem::UnregisterEvent(1, &obj) == false);

		//Event == SHRT_MAX
		assert(EventSystem::UnregisterEvent(SHRT_MAX, &obj) == false);

		//Event == -2 (one that doens't exist, but is valid)
		assert(EventSystem::UnregisterEvent(-2, &obj) == false);

		//Event == -1
		assert(EventSystem::UnregisterEvent(-1, &obj));
		assert(EventSystem::controlObjectCallbacks.empty());
	}
}
#endif

bool EventSystem::UnregisterEvent(short eventID, Game::WorldObject* obj)
{
	#ifdef _DEBUG
		Test_UnregisterEventWorldObject();
	#endif

	if (eventID <= 0)
	{
		return false;
	}

	if (EventSystem::worldObjectCallbacks.count(eventID) == 0)
	{
		return false;
	}

	auto map = EventSystem::worldObjectCallbacks.find(eventID)->second;
	map.erase(obj);

	return true;
}

bool EventSystem::UnregisterEvent(short eventID, Game::ControlObject* obj)
{
	#ifdef _DEBUG
		Test_UnregisterEventControlObject();
	#endif

	if (eventID >= 0)
	{
		return false;
	}

	if (EventSystem::controlObjectCallbacks.count(eventID) == 0)
	{
		return false;
	}

	auto map = EventSystem::controlObjectCallbacks.find(eventID)->second;
	map.erase(obj);

	return true;
}

