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

class Symulation
{
    private:
        std::priority_queue<AbstractEvent*, std::vector<AbstractEvent*>, EventCompPtr> eventQueue;
        std::ostream& os;
        size_t current_time;
    public:
        Interface* interface;
        Symulation(std::ostream& os, Interface* interface): os(os), interface(interface) {};
        void addEvent(AbstractEvent* event) noexcept;
        void execute_next() noexcept;
};