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
        std::cout<<"Addded package: "<<package->getDescription()<<" to collect"<<'\n';
        auto cityName = package->getSource()->getName();
        packagesToCollect[cityName].push_back(package);
    }
}

void Courier::performLocalActions(){
    std::cout<<"Location: "<<currentLocalization->getName()<<"\n";
    std::cout<<"Collect: "<<packagesToCollect[currentLocalization->getName()].size()<<"\n";
    std::cout<<"Deliver: "<<packagesToDeliver[currentLocalization->getName()].size()<<"\n\n";
    collectLocalPackages();
    removeLocalPackages();
}

void Courier::collectLocalPackages(){
    auto cityName = currentLocalization->getName();
    auto packages = packagesToCollect[cityName];
    std::cout<<"Tried to collect packages"<<std::endl;
    for(auto package:packages){
        std::cout<<"Addded package: "<<package->getDescription()<<" to deliver"<<'\n';

        auto destination = package->getDestination()->getName();
        packagesToDeliver[destination].push_back(package);
        package->setStatus(Status::InTransit);
        currentLoad+=*package->getVolume();
    }
    packagesToCollect[cityName].clear();
}

Dimensions Courier::getCurrentLoad() const{
    return currentLoad;
}
void Courier::setNewRoute(Route const& route){
    if(currentLocalization->getName()!=route[0]->getSrc()->getName())
        throw BadStartingRoutePoint();
    for(auto edge:route){
        currentRoute.push(edge);
    }
    currentDestination = route.back()->getDst();
}

void Courier::nextLocation(){
    if(currentRoute.empty())
        throw EmptyCourierRoute();
    auto newLocation = currentRoute.front()->getDst();
    currentLocalization = newLocation;
    currentRoute.pop();
    if(currentRoute.empty())
        notifier->notifyDestinationReaching(this);
}

void Courier::removeLocalPackages(){
    auto cityName = currentLocalization->getName();
    auto packages = packagesToDeliver[cityName];
    for(auto package:packages){
        std::cout<<"Delivered package: "<<package->getDescription()<<'\n';

        currentLoad-=*package->getVolume();
        package->setStatus(Status::Delivered);
    }
    notifier->notifyPackagesDelivery(packages);
    packagesToDeliver[cityName].clear();
}

bool Courier::canMoveForward() const{
    return currentRoute.size() > 0;
}

City* Courier::getNextTravelsal() const{
    if(currentRoute.empty())
        throw EmptyCourierRoute();
    return currentRoute.front()->getDst();
}

size_t Courier::getDistToNextTravelsal() const{
    if(currentRoute.empty())
        throw EmptyCourierRoute();
    return currentRoute.front()->getDist();
}

std::string Courier::getName() const{
    return name;
}

Dimensions* Courier::getCapacity() const{
    return capacity;
}
std::vector<AbstractPackage*> Courier::getLocalPackagesToDeliver(City* city) {
    auto cityName = city->getName();
    return packagesToDeliver[cityName];
}
std::vector<AbstractPackage*> Courier::getLocalPackagesToCollect(City* city) {
    auto cityName = city->getName();
    return packagesToCollect[cityName];
}
size_t Courier::number_of_couriers = 0;