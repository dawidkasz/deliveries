#pragma once
#include "../Symulation/Symulation.h"

class AbstractCommand
{
    private:
        Symulation* symulation;
    public:
        virtual void execute() const noexcept;
        AbstractCommand(Symulation* symulation) : symulation(symulation) {};
};

class NextStepCommand : public AbstractCommand
{
    public:
        NextStepCommand(Symulation* symulation) : AbstractCommand(symulation) {};
        void execute() const noexcept;
};

class AddPackageCommand : public AbstractCommand
{
    private:

};

class AddCourierCommand : public AbstractCommand
{
    private:
};