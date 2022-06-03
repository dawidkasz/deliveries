#pragma once
#include "../Simulation/Simulation.h"
#include <vector>
#include <string>
#include "../Command/Command.h"

class invalid_command_type : public std::logic_error
{
    using logic_error::logic_error;
    invalid_command_type(std::string message):logic_error(message){};
};

class too_little_arguments : public std::logic_error
{
    using logic_error::logic_error;
};

class CommandInterpreter
{
    private:
        Simulation* simulation;
        std::vector<std::string> split_string(std::string str) const;
    public:
        CommandInterpreter(Simulation* simulation) : simulation(simulation) {};
        AbstractCommand* generateCommand(std::string str) const;
};
