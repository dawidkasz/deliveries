#include "CommandInterpreter/CommandInterpreter.h"
#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include "../logic/Utils/Dimensions.h"
#include "../logic/Courier/CourierFactory.h"

void main_loop(CommandInterpreter& cmdInt)
{
    while(true)
    {
        std::string command_str;
        std::cout<<"> ";
        getline(std::cin, command_str);

        if(command_str=="")
            {
                AbstractCommand *cmd = cmdInt.generateCommand("next_step");
                cmd->execute();
                delete cmd;
            }
            else if(command_str == "exit")
            {
                return;
            }
            else if(command_str != "")
            {
                try{
                    AbstractCommand *cmd = cmdInt.generateCommand(command_str);
                    cmd->execute();
                    delete cmd;
                }
                catch(const invalid_command_type& e){
                    std::cout<<e.what()<<"\n";
                }
                catch(const InvalidCourierData& e)
                {
                    std::cout<<"Invalid courier data: "<<e.what()<<"\n";
                }
                catch(const too_little_arguments& e)
                {
                    std::cout<<e.what()<<"\n";
                }
            }
    }
}

int main(int argc, char *argv[])
{
    if(argc < 2){
        throw std::invalid_argument("Map config file not specified.");
    }

    Map mp;
    std::ifstream mapConfig(argv[1]);
    if (mapConfig.is_open()){
        std::stringstream ss;
        ss << mapConfig.rdbuf();
        ss >> mp;
        mapConfig.close();
    }else{
        throw std::invalid_argument("File doesn't exist.");
        return 0;
    }

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
    Simulation simulation(std::cout, &interface, 5, 5);

    CommandInterpreter cmdInt(&simulation);
    main_loop(cmdInt);
}
