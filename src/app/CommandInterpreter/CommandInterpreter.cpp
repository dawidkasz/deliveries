#include "CommandInterpreter.h"
#include <sstream>
#include <iostream>
#include <iterator>

std::vector<std::string> CommandInterpreter::split_string(std::string str) const {
    std::vector<std::string> result;
    while(str.size()){
        int index = str.find(" ");
        if(index!=std::string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index + 1);
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}


AbstractCommand* CommandInterpreter::generateCommand(std::string str) const
{
    //addcourier nazwa lokalizacja capacity
    //addpackage src dst size priority description

    auto str_split = split_string(str);
    std::string command_id = str_split[0];
    if(command_id == "next_step" || command_id == "next")
    {
        return new NextStepCommand(simulation);
    }
    else if (command_id == "addcourier")
    {
        if(str_split.size() < 4)
        {
            throw too_little_arguments("Too little arguments: " + std::to_string(str_split.size() - 1));
        }
        return new AddCourierCommand(simulation, str_split[1], str_split[2], str_split[3], str_split[2]);
    }
    else if (command_id == "addpackage")
    {
        if(str_split.size() < 6)
        {
            throw too_little_arguments("Too little arguments: " + std::to_string(str_split.size() - 1));
        }
        return new AddPackageCommand(simulation, str_split[1], str_split[2], str_split[3], str_split[4], str_split[5]);
    }
    else if (command_id == "statuscourier")
    {
        if(str_split.size() < 2)
        {
            throw too_little_arguments("Too little arguments: " + std::to_string(str_split.size() - 1));
        }
        return new StatusCourierCommand(simulation, str_split[1]);
    }
    else if (command_id == "statuspackage")
    {
        if(str_split.size() < 2)
        {
            throw too_little_arguments("Too little arguments: " + std::to_string(str_split.size() - 1));
        }
        return new StatusPackageCommand(simulation, str_split[1]);
    }
    throw invalid_command_type(("Invalid command: " + command_id).c_str());
}