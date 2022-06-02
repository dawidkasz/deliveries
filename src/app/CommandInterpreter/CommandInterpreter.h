#pragma once
#include "../Simulation/Simulation.h"
#include <vector>
#include <string>
#include "../Command/Command.h"

class invalid_command_type : std::logic_error { using logic_error::logic_error; };

class CommandInterpreter
{
    private:
        Simulation* symulation;
        std::vector<std::string> split_string(std::string str) const;
    public:
        CommandInterpreter(Simulation* symulation) : symulation(symulation) {};
        AbstractCommand* generateCommand(std::string str) const;
};