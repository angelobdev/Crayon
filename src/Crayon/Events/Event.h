#pragma once

#include "crypch.h"

namespace Crayon
{
	// BASE EVENT CLASS
	class Event
	{
	protected:
		bool m_IsNull;

	public:
		Event() : m_IsNull(true) {}
		~Event() {}

		virtual std::string GetName() const { return "Null"; }

		bool IsNull() const { return m_IsNull; }
	};

	// EVENT DISPATCHER CLASS
	class EventDispatcher // Todo: Maybe async
	{
	private:
		static std::queue<Event*> s_Events;

	public:
		static void Dispatch(Event* event);
		static Event* Retrieve();

		static int GetQueueSize() { return s_Events.size(); }
	};

	inline std::ostream& operator<< (std::ostream& os, const Event& event)
	{
		os << event.GetName();
		return os;
	}

}