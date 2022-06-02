#include "CommandInterpreter/CommandInterpreter.h"
#include <iostream>
#include "../logic/Utils/Dimensions.h"

void main_loop(CommandInterpreter& cmdInt)
{
    while(true)
    {
        std::string command_str;
        std::cout<<"> ";
        std::cin>>command_str;
        auto cmd = cmdInt.generateCommand(command_str);
        cmd->execute();
    }
}

int main()
{
    Map mp;
    // Load cities from file
    typedef std::unordered_map<std::string, Dimensions*> Sizes;
    Sizes packageDimensions = {
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    };
    Sizes courierCapacities = {
        {"small", new Dimensions(100)},
        {"middle", new Dimensions(200)},
        {"big", new Dimensions(300)},
    };
    Interface interface(packageDimensions, courierCapacities, &mp);
    Simulation simulation(std::cout, &interface);
    CommandInterpreter cmdInt(&simulation);
    main_loop(cmdInt);
}
