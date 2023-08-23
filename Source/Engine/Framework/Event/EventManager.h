#pragma once
#include "Event.h"
#include "Framework/Singleton.h"
#include <map>
#include <list>
#include <functional>
namespace cg
	#define EVENT_SUBSCRIBE(id, function)	kiko::EventManager::Instance().Subscribe(id, this, std::bind(&function, this, std::placeholders::_1));
	#define EVENT_UNSUBSCRIBE(id)			kiko::EventManager::Instance().Unsubscribe(id, this);
{
	class IEventListener
	{
		//
	};
	class EventManager : public Singleton<EventManager>
	{
	public:
		using eventFunction = std::function<void(const Event&)>;
		struct EventDispatcher
		{
			IEventListener* listener = nullptr;
			eventFunction function;
		};
		friend class Singleton;
	public:
		void Update(float dt);

		void Subscribe(Event::id_t id, IEventListener* listener, eventFunction function);
		void Unsubscribe(Event::id_t id, IEventListener* listener);

		void DispatchEvent(Event::id_t id, Event::data_t data);
	private:
		EventManager() = default;
		std::map<Event::id_t, std::list<EventDispatcher>> m_dispatchers;
	};
}