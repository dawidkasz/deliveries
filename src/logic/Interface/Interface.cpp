#include "Interface.h"

bool Interface::moveCourierForward(Courier* courier){
    try{
        courier->nextLocation();
    }
    catch(EmptyCourierRoute const& e){
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
    couriers[courier->getID()] = courier;
    availableCouriers.insert(courier);
}

AbstractPackage* Interface::getPackage(std::string id) {
    return packages[id];
}

void Interface::addPackage(AbstractPackage* package){
    packages[package->getID()] = package;
    unhandledPackages.push_back(package);
}

void Interface::notifyDestinationReaching(Courier* courier){
    availableCouriers.insert(courier);
}

bool Interface::isAvailable(Courier* c){
    return availableCouriers.find(c)!=availableCouriers.end();
}

std::vector<Courier*> Interface::assignUnhandledPackages(){
    std::unordered_map<Courier*, Dimensions> potentialCourierLoad;
    std::unordered_map<Courier*, std::unordered_set<City*>> usedCouriers;
    std::vector<AbstractPackage*> handledPackages;

    for(AbstractPackage* package : unhandledPackages){
        std::unordered_map<City*, size_t> distances = map->getAllDistances(package->getSource()).first;

        size_t minDist = ULONG_MAX;
        Courier* assignedCourier = nullptr;
        for(auto pairIdCourier : couriers){
            Courier* courier = pairIdCourier.second;
            if(!isAvailable(courier) || potentialCourierLoad[courier] + *package->getVolume() > *courier->getCapacity())
                continue;

            if(assignedCourier == nullptr || distances[courier->getCurrentLocation()] < minDist){
                assignedCourier = courier;
                minDist = distances[courier->getCurrentLocation()];
            }
        }

        if(assignedCourier){
            assignedCourier->addPackagesToCollect({package});
            potentialCourierLoad[assignedCourier] += *package->getVolume();
            usedCouriers[assignedCourier].insert(package->getSource());
            usedCouriers[assignedCourier].insert(package->getDestination());
            handledPackages.push_back(package);
        }
    }

    for(AbstractPackage* package : handledPackages)
        unhandledPackages.erase(std::find(unhandledPackages.begin(), unhandledPackages.end(), package));

    std::vector<Courier*> couriersToSend;
    for(auto it : usedCouriers){
        Courier* courier = it.first;
        std::vector<City*> citiesOnRoute = {courier->getCurrentLocation()};
        for(City* c : it.second){
            citiesOnRoute.push_back(c);
        }

        std::vector<Edge*> newRoute = map->getOptimalRoute(citiesOnRoute, courier->getCurrentLocation());
        courier->setNewRoute(newRoute);
        couriersToSend.push_back(courier);
    }

    return couriersToSend;
}

size_t Interface::numOfUnhandledPackages(){
    return unhandledPackages.size();
}

size_t Interface::numOfAvailableCouriers(){
    return availableCouriers.size();
}