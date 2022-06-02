#include "Symulation.h"

void Symulation::addEvent(AbstractEvent* event) noexcept
{
    eventQueue.push(event);
}

void Symulation::execute_next() noexcept
{
    auto to_execute = eventQueue.top();
    to_execute->execute();
    os<<to_execute->what();
    delete to_execute;
    eventQueue.pop();
}