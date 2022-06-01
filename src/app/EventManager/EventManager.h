#include <queue>
#include "../Event/Event.h"

class EventManager
{
    private:
        std::priority_queue<AbstractEvent*, std::vector<AbstractEvent*>, std::greater<AbstractEvent*>> eventQueue;
        std::ostream& os;
    public:
        EventManager(std::ostream& os): os(os) {};
        void addEvent(AbstractEvent* event) noexcept;
        void execute_next() noexcept;
};