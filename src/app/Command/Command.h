#pragma once
#include "../Simulation/Simulation.h"


class AbstractCommand
{
    public:
        virtual void execute() const = 0;
};

class NextStepCommand : public AbstractCommand
{
    private:
        Simulation* simulation;
    public:
        NextStepCommand(Simulation* simulation) : simulation(simulation) {};
        void execute() const;
};

class AddPackageCommand : public AbstractCommand
{
    private:
        Simulation* simulation;
        std::string sourceCity;
        std::string destinationCity;
        std::string size;
        int priority;
        std::string description;
    public:
        AddPackageCommand(Simulation* simulation, std::string sourceCity, std::string destinationCity, std::string size, std::string priority, std::string description) :
            simulation(simulation), sourceCity(sourceCity), destinationCity(destinationCity), size(size), priority(stoi(priority)), description(description) {};
        void execute() const;
};

class AddCourierCommand : public AbstractCommand
{
    private:
        Simulation* simulation;
        std::string name;
        std::string defaultLocalization;
        std::string capacity;
        std::string currentLocalization;
    public:
        AddCourierCommand(Simulation* simulation, std::string name, std::string defaultLocalization, std::string capacity, std::string currentLocalization) :
            simulation(simulation), name(name), defaultLocalization(defaultLocalization), capacity(capacity), currentLocalization(currentLocalization) {};
        void execute() const;
};

class StatusCourierCommand : public AbstractCommand
{
    private:
        Simulation* simulation;
        Courier* courier;
    public:
        StatusCourierCommand(Simulation* simulation, std::string id) : simulation(simulation), courier(simulation->interface->getCourier(stoi(id))) {};
        void execute() const;

};

class StatusPackageCommand : public AbstractCommand
{
    private:
        Simulation* simulation;
        AbstractPackage* package;
    public:
        StatusPackageCommand(Simulation* simulation, std::string id) : simulation(simulation), package(simulation->interface->getPackage(id)) {};
        void execute() const;
};