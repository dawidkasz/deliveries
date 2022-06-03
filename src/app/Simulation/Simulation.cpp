#include "Simulation.h"


bool EventCompPtr::operator()(AbstractEvent* a, AbstractEvent* b)
{
    return *a > *b;
}

void Simulation::addEvent(AbstractEvent* event) noexcept
{
    eventQueue.push(event);
}


void Simulation::executeAllNext() noexcept
{
    ++timeWithoutPackages;

    if(interface->numOfAvailableCouriers()){
        if(timeWithoutPackages >= addPackagesTimeout && interface->numOfUnhandledPackages() > 0){
            eventQueue.push(new AssignPackagesEvent(this, current_time));
        }else if(interface->numOfUnhandledPackages() > unhandledPackagesTreshold){
            eventQueue.push(new AssignPackagesEvent(this, current_time));
        }
    }

    if(eventQueue.empty())
        return;

    current_time = eventQueue.top()->getTime();

    while(!eventQueue.empty() && eventQueue.top()->getTime() == current_time)
    {
        AbstractEvent* to_execute = eventQueue.top();
        eventQueue.pop();

        to_execute->execute();
        os<<to_execute->what();
        delete to_execute;
    }
}

size_t Simulation::getCurrentTime() const{
    return current_time;
}

void Simulation::setTimeWithoutPackages(size_t time){
    timeWithoutPackages = time;
}


Simulation::~Simulation(){
    while(!eventQueue.empty()){
        AbstractEvent* event = eventQueue.top();
        eventQueue.pop();
        delete event;
    }
}