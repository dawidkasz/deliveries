#include <queue>
#include "../Event/Event.h"

class EventManager
{
    private:
        std::queue<AbstractEvent*> eventQueue;
    public:
        EventManager() = default;
        void addEvent(AbstractEvent* event) noexcept;
        void printAndFlushEvents() noexcept;
};