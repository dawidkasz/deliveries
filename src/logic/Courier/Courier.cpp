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
// void addPackages(std::vector<AbstractPackage*> & packages);
// void removeLocalPackages();
// bool canDeliverPackage(AbstractPackage const& package) const;
// void nextLocaction();
// void setNewRoute(std::vector<std::shared_ptr<City> > route);
// size_t getReachTime() const;