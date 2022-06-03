#include "Command.h"
#include <iostream>
void NextStepCommand::execute() const
{
    simulation->executeAllNext();
}

void AddPackageCommand::execute() const
{
    Package* package = simulation->interface->packageFactory.createPackage(sourceCity, destinationCity, size, priority, description);
    simulation->interface->addPackage(package);
    std::cout<<"Package added!\nPackage ID: "<<package->getID()<<'\n';

    simulation->setTimeWithoutPackages(0);
}

void AddCourierCommand::execute() const
{
    Courier* courier = simulation->interface->courierFactory.createCourier(name, defaultLocalization, capacity, currentLocalization);
    simulation->interface->addCourier(courier);
    std::cout<<"Courier added!\nCourier ID: "<<courier->getID()<<'\n';
}

void StatusCourierCommand::execute() const
{
    std::string output;
    output += "Courier " + courier->getName() + " [" + std::to_string(courier->getID()) + "] ";
    output += "is at " + courier->getCurrentLocation()->getName() + "\n";
    std::cout<<output;
}

void StatusPackageCommand::execute() const
{
    std::cout<<*package;
}