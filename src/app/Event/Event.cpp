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

    if(courier->canMoveForward())
        simulation->addEvent(new ArriveAtLocEvent(simulation, courier, courier->getNextTravelsal(), currentTime + courier->getDistToNextTravelsal()));

    std::vector<AbstractPackage*> packagesToDeliver = courier->getLocalPackagesToDeliver(currentLocaction);
    if(!packagesToDeliver.empty()){
        simulation->addEvent(new DeliveryEvent(simulation, courier, currentLocaction, packagesToDeliver, currentTime));
    }

    std::vector<AbstractPackage*> packagesToCollect = courier->getLocalPackagesToCollect(currentLocaction);
    if(!packagesToCollect.empty()){
        simulation->addEvent(new PickupPackageEvent(simulation, courier, currentLocaction, packagesToCollect, currentTime));
    }

}

void PickupPackageEvent::execute() const
{
   courier->collectLocalPackages();
}

void AssignPackagesEvent::execute() const{
    simulation->setTimeWithoutPackages(0);

    std::cout<<simulation->interface->numOfUnhandledPackages()<<std::endl;
    std::vector<Courier*> couriers = simulation->interface->assignUnhandledPackages();
    for(Courier* courier : couriers){

        size_t nextTime = simulation->getCurrentTime() + courier->getDistToNextTravelsal();
        simulation->addEvent(new ArriveAtLocEvent(simulation, courier, courier->getNextTravelsal(), nextTime));
    }
}