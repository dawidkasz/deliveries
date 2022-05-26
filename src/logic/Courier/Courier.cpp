#include "Courier.h"


size_t Courier::getID() const{
    return id;
}

std::shared_ptr<City> Courier::getCurrentLocation() const{
    return currentLocalization;
}
std::shared_ptr<City> Courier::getDestination() const{
    return currentDestination;
}
// void addPackages(std::vector<AbstractPackage*> & packages);
// void removeLocalPackages();
// bool canDeliverPackage(AbstractPackage const& package) const;
// void nextLocaction();
// void setNewRoute(std::vector<std::shared_ptr<City> > route);
// size_t getReachTime() const;