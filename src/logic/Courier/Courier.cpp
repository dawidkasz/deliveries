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
        // currentLoad+=*package->getVolume();
    }
}

void Courier::performLocalActions(){
    collectLocalPackages();
}

void Courier::collectLocalPackages(){
    auto cityName = currentLocalization->getName();
    auto packages = packagesToCollect[cityName];
    for(auto package:packages){
        packagesToDeliver[cityName].push_back(package);
        currentLoad+=*package->getVolume();
    }
    packagesToCollect[cityName].clear();
}

Dimensions Courier::getCurrentLoad() const{
    return currentLoad;
}
// void removeLocalPackages();
// bool canDeliverPackage(AbstractPackage const& package) const;
// void nextLocaction();
// void setNewRoute(std::vector<std::shared_ptr<City> > route);
// size_t getReachTime() const;