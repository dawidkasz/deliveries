#pragma once
#include <queue>
#include "../Event/Event.h"
#include "../../logic/Interface/Interface.h"

class EventCompPtr
{
    public:
        bool operator()(AbstractEvent* a, AbstractEvent* b)
        {
            return *a < *b;
        }
};

class Simulation
{
    private:
        std::priority_queue<AbstractEvent*, std::vector<AbstractEvent*>, EventCompPtr> eventQueue;
        std::ostream& os;
        size_t current_time;
    public:
        Interface* interface;
        Simulation(std::ostream& os, Interface* interface): os(os), interface(interface), current_time(0) {};
        void addEvent(AbstractEvent* event) noexcept;
        void execute_next() noexcept;
};