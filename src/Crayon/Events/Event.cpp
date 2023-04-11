#include "Event.h"

namespace Crayon
{
    std::queue<Event *> EventDispatcher::s_Events = std::queue<Event *>();

    void EventDispatcher::Dispatch(Event *event)
    {
        //CRAYON_CORE_TRACE("Dispatching {}", event->GetName());
        if (!event->IsNull())
            s_Events.push(event);
    }

    Event *EventDispatcher::Retrieve()
    {
        if (s_Events.empty())
            return nullptr;

        Event *toHandle = s_Events.front();
        s_Events.pop();
        return toHandle;
    }
}