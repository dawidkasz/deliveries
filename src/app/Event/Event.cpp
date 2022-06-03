#include <string>
#include "Event.h"

std::string DeliveryEvent::what() const noexcept
{
    std::string result = "";
    for(auto package:packages){
    result += "Courier " + courier->getName() + " [" + std::to_string(courier->getID()) + "]";
    result += " delivered package " + package->getDescription();
    result += " to city " + city->getName() + "\n";
    }
    return result;
};

std::string ArriveAtLocEvent::what() const noexcept
{
    std::string result;
    result += "Courier " + courier->getName() + " [" + std::to_string(courier->getID()) + "]";
    result += " arrived at " + city->getName() + "\n";
    return result;
};

std::string PickupPackageEvent::what() const noexcept
{
    std::string result = "";
    for(auto package:packages){
    result += "Courier " + courier->getName() + " [" + std::to_string(courier->getID()) + "]";
    result += " collected package " + package->getDescription();
    result += " from city " + city->getName() + "\n";
    }
    return result;
};

std::string AssignPackagesEvent::what() const noexcept{
    return "Packages have been assigned to couriers\n";
}


void DeliveryEvent::execute() const
{
   courier->removeLocalPackages();
}

void ArriveAtLocEvent::execute() const
{
    if(courier->canMoveForward())
        simulation->interface->moveCourierForward(courier);

    City* currentLocaction = courier->getCurrentLocation();
    size_t currentTime = simulation->getCurrentTime();
    auto packagesToDeliver = courier->getLocalPackagesToDeliver(currentLocaction);

    std::cout<<"ToDeliver: "<<packagesToDeliver.size()<<"\n";

    if(courier->canMoveForward())
        simulation->addEvent(new ArriveAtLocEvent(simulation, courier, courier->getNextTravelsal(), currentTime + courier->getDistToNextTravelsal()));

    if(!packagesToDeliver.empty()){
        std::cout<<"Add deliver event\n";
        simulation->addEvent(new DeliveryEvent(simulation, courier, currentLocaction, packagesToDeliver, currentTime));
    }
    auto packagesToCollect = courier->getLocalPackagesToCollect(currentLocaction);
    if(!packagesToCollect.empty()){
        std::cout<<"Add pickup package event\n";
        simulation->addEvent(new PickupPackageEvent(simulation, courier, currentLocaction, packagesToCollect, currentTime));
    }
    std::cout<<"ToCollect: "<<packagesToCollect.size()<<"\n";
}

void PickupPackageEvent::execute() const
{
   courier->collectLocalPackages();
}

void AssignPackagesEvent::execute() const{
    simulation->setTimeWithoutPackages(0);

    std::cout<<simulation->interface->numOfUnhandledPackages()<<std::endl;
    std::vector<Courier*> couriers = simulation->interface->assignUnhandledPackages();
    for(auto courier:couriers){

        size_t nextTime = simulation->getCurrentTime() + courier->getDistToNextTravelsal();
        simulation->addEvent(new ArriveAtLocEvent(simulation, courier, courier->getNextTravelsal(), nextTime));
    }
}