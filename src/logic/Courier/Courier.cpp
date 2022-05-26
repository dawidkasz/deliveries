#include "Courier.h"


size_t Courier::getID() const{
    return id;
}

City* Courier::getCurrentLocation() const{
    return currentLocalization;
}
City* Courier::getDestination() const{
    return currentDestination;
}

bool Courier::operator==(Courier const& courier) const{
    return this->getID() == courier.getID();
}

bool Courier::operator!=(Courier const& courier) const{
    return !(*this == courier);
}
void Courier::addPackagesToCollect(std::vector<AbstractPackage*> const& packages){
    for(auto package:packages){
        auto cityName = package->getSource()->getName();
        packagesToCollect[cityName].push_back(package);
    }
}

void Courier::performLocalActions(){
    collectLocalPackages();
    removeLocalPackages();
}

void Courier::collectLocalPackages(){
    auto cityName = currentLocalization->getName();
    auto packages = packagesToCollect[cityName];
    for(auto package:packages){
        auto destination = package->getDestination()->getName();
        packagesToDeliver[destination].push_back(package);
        currentLoad+=*package->getVolume();
    }
    packagesToCollect[cityName].clear();
}

Dimensions Courier::getCurrentLoad() const{
    return currentLoad;
}
void Courier::setNewRoute(Route const& route){
    for(auto edge:route.second){
        currentRoute.push(std::make_pair(edge->getDist(), edge->getDst()));
    }
    currentDestination = route.second.back()->getDst();
    performLocalActions();
}

void Courier::nextLocaction(){
    auto newLocation = currentRoute.front().second;
    currentLocalization = newLocation;
    currentRoute.pop();
    performLocalActions();
}

void Courier::removeLocalPackages(){
    auto cityName = currentLocalization->getName();
    auto packages = packagesToDeliver[cityName];
    for(auto package:packages){
        currentLoad-=*package->getVolume();
    }
    packagesToDeliver[cityName].clear();
}
// bool canDeliverPackage(AbstractPackage const& package) const;
// void nextLocaction();
// size_t getReachTime() const;