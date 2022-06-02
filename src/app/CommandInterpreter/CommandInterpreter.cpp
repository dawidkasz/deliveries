#include "CommandInterpreter.h"
#include <sstream>
#include <iostream>

std::vector<std::string> CommandInterpreter::split_string(std::string str) const
{
    std::vector<std::string> output;
    std::istringstream f(str);
    std::string s;
    while (getline(f, s, ';'))
    {
        output.push_back(s);
    }
    return output;
}

AbstractCommand* CommandInterpreter::generateCommand(std::string str) const
{
    auto str_split = split_string(str);
    std::string command_id = str_split[0];
    if(command_id == "next_step" || command_id == "next")
    {
        return new NextStepCommand(simulation);
    }
    throw invalid_command_type("Invalid command: " + command_id);
}