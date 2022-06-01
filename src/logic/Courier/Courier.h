#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>
#include "../Package/AbstractPackage.h"
#include "../Utils/ObjectsExceptions.h"
#include "../Interface/INotify.h"

class Courier{
    typedef std::unordered_map<std::string, std::vector<AbstractPackage*> > Container;
    typedef std::pair<size_t, std::vector<Edge*> > Route;
    typedef std::queue<std::pair<size_t, City* > > RouteQueue;
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
    void removeLocalPackages();
    void collectLocalPackages();
    INotify* notifier=nullptr;
    public:
    Courier()=default;
    Courier(std::string name, City* defaultLocalization, Dimensions* capacity, City* currentLocalization=nullptr, INotify* notifier=nullptr)
    :name(name), defaultLocalization(defaultLocalization), capacity(capacity),currentLocalization(currentLocalization), notifier(notifier), id(++number_of_couriers){
    };
    bool operator==(Courier const& courier) const;
    bool operator!=(Courier const& courier) const;
    size_t getID() const;
    void addPackagesToCollect(std::vector<AbstractPackage*> const& packages);
    void performLocalActions();
    bool canDeliverPackage(AbstractPackage const& package) const;
    void nextLocaction();
    void setNewRoute(Route const& route);
    City* getDestination() const;
    City* getCurrentLocation() const;
    Dimensions getCurrentLoad() const;
    std::pair<size_t, City* > getNextTravelsal() const;
};