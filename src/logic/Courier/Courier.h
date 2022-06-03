#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>
#include "../Package/AbstractPackage.h"
#include "../Utils/ObjectsExceptions.h"
#include "../Interface/INotify.h"

class Courier
{
    typedef std::unordered_map<std::string, std::vector<AbstractPackage*> > Container;
    typedef std::vector<Edge*> Route;
    typedef std::queue<Edge*> RouteQueue;
    static size_t number_of_couriers;
    size_t id;
    std::string name;
    City* currentLocalization;
    City* currentDestination=nullptr;
    RouteQueue currentRoute;
    City* defaultLocalization;
    Dimensions* capacity;
    Container packagesToCollect;
    Container packagesToDeliver;
    Dimensions currentLoad;
    INotify* notifier=nullptr;
public:
    Courier()=default;
    Courier(std::string name, City* defaultLocalization, Dimensions* capacity, City* currentLocalization=nullptr, INotify* notifier=nullptr)
    :name(name), defaultLocalization(defaultLocalization), capacity(capacity),currentLocalization(currentLocalization), notifier(notifier), id(++number_of_couriers){
    };
    void removeLocalPackages();
    void collectLocalPackages();
    bool operator==(Courier const& courier) const;
    bool operator!=(Courier const& courier) const;
    size_t getID() const;
    void addPackagesToCollect(std::vector<AbstractPackage*> const& packages);
    void performLocalActions();
    bool canMoveForward() const;
    void nextLocation();
    void setNewRoute(Route const& route);
    std::string getName() const;
    City* getDestination() const;
    City* getCurrentLocation() const;
    Dimensions getCurrentLoad() const;
    Dimensions* getCapacity() const;
    City* getNextTravelsal() const;
    size_t getDistToNextTravelsal() const;
    std::vector<AbstractPackage*> getLocalPackagesToDeliver(City* city);
    std::vector<AbstractPackage*> getLocalPackagesToCollect(City* city);
};
