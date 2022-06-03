#pragma once
#include <queue>
#include "../Event/Event.h"
#include "../../logic/Interface/Interface.h"


class AbstractEvent;


class EventCompPtr
{
    public:
        bool operator()(AbstractEvent* a, AbstractEvent* b);
};


class Simulation
{
    private:
        std::priority_queue<AbstractEvent*, std::vector<AbstractEvent*>, EventCompPtr> eventQueue;
        std::ostream& os;
        size_t current_time;
        size_t addPackagesTimeout;
        size_t timeWithoutPackages;
        size_t unhandledPackagesTreshold;
    public:
        Interface* interface;
        Simulation(std::ostream& os, Interface* interface, size_t addPackagesTimeout, size_t unhandledPackagesTreshold)
            : os(os), interface(interface), current_time(0), addPackagesTimeout(addPackagesTimeout),
              unhandledPackagesTreshold(unhandledPackagesTreshold), timeWithoutPackages(0) {};
        void addEvent(AbstractEvent* event) noexcept;
        void executeAllNext() noexcept;

        void setTimeWithoutPackages(size_t time);
        size_t getCurrentTime() const;

        ~Simulation();
};