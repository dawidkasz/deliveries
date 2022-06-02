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
    if(currentLocalization->getName()!=route.second[0]->getSrc()->getName())
        throw BadStartingRoutePoint();
    for(auto edge:route.second){
        currentRoute.push(std::make_pair(edge->getDist(), edge->getDst()));
    }
    currentDestination = route.second.back()->getDst();
}

void Courier::nextLocation(){
    if(currentRoute.empty())
        throw EmptyCourierRoute();
    auto newLocation = currentRoute.front().second;
    currentLocalization = newLocation;
    currentRoute.pop();
}

void Courier::removeLocalPackages(){
    auto cityName = currentLocalization->getName();
    auto packages = packagesToDeliver[cityName];
    for(auto package:packages){
        currentLoad-=*package->getVolume();
        package->setStatus(Status::Delivered);
    }
    notifier->notifyPackagesDelivery(packages);
    packagesToDeliver[cityName].clear();
}

std::pair<size_t, City* > Courier::getNextTravelsal() const{
    if(currentRoute.empty())
        throw EmptyCourierRoute();
    return currentRoute.front();
}
// bool canDeliverPackage(AbstractPackage const& package) const;

std::string Courier::getName() const{
    return name;
}

size_t Courier::number_of_couriers = 0;