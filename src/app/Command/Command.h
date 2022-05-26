#include "../../logic/Interface/Interface.h"

class AbstractCommand
{
    public:
        virtual void execute() const noexcept;
};

class NextStepCommand : public AbstractCommand
{
    private:
        Interface* interface;
    public:
        NextStepCommand(Interface* interface) : interface(interface) {};
        void execute() const noexcept;
};
