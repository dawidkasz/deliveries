#pragma once
#include "../Simulation/Simulation.h"

class AbstractCommand
{
    private:
        Simulation* symulation;
    public:
        virtual void execute() const noexcept;
        AbstractCommand(Simulation* symulation) : symulation(symulation) {};
};

class NextStepCommand : public AbstractCommand
{
    public:
        NextStepCommand(Simulation* symulation) : AbstractCommand(symulation) {};
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