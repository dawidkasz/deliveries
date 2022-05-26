#include "EventManager.h"

void EventManager::addEvent(AbstractEvent* event) noexcept
{
    eventQueue.push(event);
}

void EventManager::printAndFlushEvents() noexcept
{
    while(!eventQueue.empty())
    {
        auto event = eventQueue.back();
        std::cout<<event->getStr();
        eventQueue.pop();
        delete event;
    }
}