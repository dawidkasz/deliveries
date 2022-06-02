#include "Simulation.h"

void Simulation::addEvent(AbstractEvent* event) noexcept
{
    eventQueue.push(event);
}

void Simulation::executeAllNext() noexcept
{
    current_time = eventQueue.top()->getTime();
    while(eventQueue.top()->getTime() == current_time)
    {
        auto to_execute = eventQueue.top();
        to_execute->execute();
        os<<to_execute->what();
        delete to_execute;
        eventQueue.pop();
    }
}