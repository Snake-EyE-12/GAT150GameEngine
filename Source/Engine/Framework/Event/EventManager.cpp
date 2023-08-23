#include "EventManager.h"
#include "Core/Logger.h"

namespace cg
{
	void cg::EventManager::Update(float dt)
	{
	}

	void cg::EventManager::Subscribe(Event::id_t id, IEventListener* listener, eventFunction function)
	{
		EventDispatcher dispatcher;
		dispatcher.listener = listener;
		dispatcher.function = function;

		INFO_LOG("Event Subscribed: " << id);

		m_dispatchers[id].push_back(dispatcher);
	}

	void cg::EventManager::Unsubscribe(Event::id_t id, IEventListener* listener)
	{
		// get list of dispatchers for event
		auto& dispatchers = m_dispatchers[id];

		// remove dipatcher with matching listener
		for (auto iter = dispatchers.begin(); iter != dispatchers.end(); iter++)
		{
			if (iter->listener == listener)
			{
				INFO_LOG("Event unsubscribed: " << id);

				dispatchers.erase(iter);
				break;
			}
		}
	}

	void cg::EventManager::DispatchEvent(Event::id_t id, Event::data_t data)
	{
		Event event{ id, data };
		if (m_dispatchers.find(id) != m_dispatchers.end()) {
			auto& dispatchers = m_dispatchers[id];
			for (auto& dispatcher : dispatchers) {
				dispatcher.function(event);
			}
		}
	}
}