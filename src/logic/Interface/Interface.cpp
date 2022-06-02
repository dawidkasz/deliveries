#include "Interface.h"

bool Interface::moveCourierForward(Courier* courier){
    try{
        courier->nextLocaction();
    }catch(EmptyCourierRoute const& e){
        return false;
    }
    return true;
}

void Interface::performCourierActions(Courier* courier){
    courier->performLocalActions();
}

void Interface::setCourierNewRoute(Courier* courier, Interface::Route const& route){
    availableCouriers.erase(courier);
    courier->setNewRoute(route);
}

void Interface::assignCourierPackages(Courier* courier, std::vector<AbstractPackage*> const& packages){
    courier->addPackagesToCollect(packages);
}
void Interface::notifyPackagesDelivery(std::vector<AbstractPackage*> const& packages){
    for(auto p:packages)
        packagesArchive.push_back(p);
}

Courier* Interface::getCourier(size_t id) {
    return couriers[id];
}

void Interface::addCourier(Courier* courier){
    couriers.emplace(courier->getID(), courier);
    availableCouriers.insert(courier);
}

AbstractPackage* Interface::getPackage(std::string id) {
    return packages[id];
}

void Interface::addPackage(AbstractPackage* package){
    packages.emplace(package->getID(), package);
    unhandledPackages.push_back(package);
}

void Interface::notifyDestinationReaching(Courier* courier){
    availableCouriers.insert(courier);
}

bool Interface::isAvailable(Courier* c){
    return availableCouriers.find(c)!=availableCouriers.end();
}

