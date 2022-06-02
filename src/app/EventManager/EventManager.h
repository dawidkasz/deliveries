#include <queue>
#include "../Event/Event.h"
class EventCompPtr
{
    bool operator()(AbstractEvent* a, AbstractEvent* b)
    {
        return *a < *b;
    }
};

class EventManager
{
    private:
        std::priority_queue<AbstractEvent*, std::vector<AbstractEvent*>, EventCompPtr> eventQueue;
        std::ostream& os;
        size_t current_time;
    public:
        EventManager(std::ostream& os): os(os){};
        void addEvent(AbstractEvent* event) noexcept;
        void execute_next() noexcept;
};