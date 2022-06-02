#include "CommandInterpreter/CommandInterpreter.h"
#include <iostream>

void main_loop()
{
    std::string command_str;
    std::cout<<"> ";
    std::cin>>command_str;
    main_loop();
}

int main()
{
    main_loop();
}
