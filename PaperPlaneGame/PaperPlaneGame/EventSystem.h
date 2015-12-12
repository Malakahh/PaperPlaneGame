#pragma once
#include <unordered_map>
#include <map>
#include "WorldObject.h"
#include "ControlObject.h"
#include <functional>
#include <assert.h>


#pragma region WorldObjectEvents
//Convention: events should have a value > 0

#define EVENT_WORLDOBJECT_UPDATE 1


#pragma endregion

#pragma region ControlObjectEvents
//Convention: events should have a value < 0

#define EVENT_CONTROLOBJECT_UPDATE -1


#pragma endregion

namespace EventSystem
{
	extern std::unordered_map<short, std::map<Game::WorldObject*, void*>> worldObjectCallbacks;
	extern std::unordered_map<short, std::map<Game::ControlObject*, void*>> controlObjectCallbacks;

	//Registers an event
	//	eventID	:	ID of the event to register (see defines)
	//	callback	:	function to call when the event is fired
	//	obj	:	A pointer to whatever object is registering the event
	//	@return	:	True if successful, otherwise false
	bool RegisterEvent(short eventID, void* callback, Game::WorldObject* obj);

	//Registers an event
	//	eventID	:	ID of the event to register (see defines)
	//	callback	:	function to call when the event is fired
	//	obj	:	A pointer to whatever object is registering the event
	//	@return	:	True if successful, otherwise false
	bool RegisterEvent(short eventID, void* callback, Game::ControlObject* obj);
	
	//Unregisters an event
	//	eventID	:	ID of the event to register (see defines)
	//	obj	:	A pointer to whatever object is unregistering the event
	//	@return	:	True if successful, otherwise false
	bool UnregisterEvent(short eventID, Game::WorldObject* obj);

	//Unregisters an event
	//	eventID	:	ID of the event to register (see defines)
	//	obj	:	A pointer to whatever object is unregistering the event
	//	@return	:	True if successful, otherwise false
	bool UnregisterEvent(short eventID, Game::ControlObject* obj);

	//Gets the callbacks for a given event
	//	T	:	Callback signature of event
	//	eventID	:	ID of the event callbacks (see defines)
	//	obj	:	Game::WorldObject (used for overloading of function)
	//	@return	:	Collection of callbacks
	template<typename T> std::vector<std::function<T>> GetEventCallbacks(short eventID, Game::WorldObject* obj)
	{
		std::vector<std::function<T>> vec;
		auto eventMap = worldObjectCallbacks.find(eventID)->second;
		std::map<Game::WorldObject*, void*>::iterator begin = eventMap.begin();
		std::pair<Game::WorldObject*, void*> end = *eventMap.rbegin();

		do
		{
			vec.push_back(std::function<T>((T*)begin->second));
		} while (eventMap.value_comp()(*begin++, end));

		return vec;
	}

	//Gets the callbacks for a given event
	//	T	:	Callback signature of event
	//	eventID	:	ID of the event callbacks (see defines)
	//	obj	:	Game::ControlObject (used for overloading of function)
	//	@return	:	Collection of callbacks
	template<typename T> std::vector<std::function<T>> GetEventCallbacks(short eventID, Game::ControlObject* obj)
	{
		std::vector<std::function<T>> vec;
		auto eventMap = controlObjectCallbacks.find(eventID)->second;
		std::map<Game::ControlObject*, void*>::iterator begin = eventMap.begin();
		std::pair<Game::ControlObject*, void*> end = *eventMap.rbegin();

		do
		{
			vec.push_back(std::function<T>((T*)begin->second));
		} while (eventMap.value_comp()(*begin++, end));

		return vec;
	}
	
	//Gets the callback for given event and object
	//	T	:	Callback signature of event
	//	eventID	:	ID of the event to fire (see defines)
	//	obj	:	Target of the event
	template <typename T> std::function<T> GetTargetedEventCallback(short eventID, Game::WorldObject* obj)
	{
		auto callback = worldObjectCallbacks.find(eventID)->second.find(obj)->second;
		return std::function<T>((T*)callback);
	}

	//Gets the callback for given event and object
	//	T	:	Callback signature of event
	//	eventID	:	ID of the event to fire (see defines)
	//	obj	:	Target of the event
	template<typename T> std::function<T> GetTargetedEventCallback(short eventID, Game::ControlObject* obj)
	{
		auto callback = controlObjectCallbacks.find(eventID)->second.find(obj)->second;
		return std::function<T>((T*)callback);
	}
	
};

