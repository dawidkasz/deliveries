#pragma once
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "../Courier/Courier.h"
#include "../Courier/CourierFactory.h"
#include "../Package/PackageFactory.h"
#include "../../map/Map/Map.h"
#include "INotify.h"


class Interface:public INotify{
    typedef std::vector<Edge*> Route;
    typedef std::unordered_map<std::string, Dimensions*> Sizes;
    std::unordered_map<size_t, Courier*> couriers;
    std::unordered_set<Courier*> availableCouriers;
    std::unordered_map<std::string, AbstractPackage*> packages;
    std::vector<AbstractPackage*> unhandledPackages;
    std::vector<AbstractPackage*> packagesArchive;
    Map* map;
protected:
    void notifyPackagesDelivery(std::vector<AbstractPackage*> const& packages);
    void notifyDestinationReaching(Courier* courier);
public:
    PackageFactory packageFactory;
    CourierFactory courierFactory;
    Interface()=default;
    Interface(Sizes const& packagesDimension, Sizes const& couriersCapacity, Map* map)
        : map(map), packageFactory(PackageFactory(packagesDimension, map)),
          courierFactory(CourierFactory(couriersCapacity, map, this)){};

    Courier* getCourier(size_t id) ;
    AbstractPackage* getPackage(std::string id);
    void addCourier(Courier* courier);
    void addPackage(AbstractPackage* package);
    bool moveCourierForward(Courier* courier);
    void performCourierActions(Courier* courier);
    void setCourierNewRoute(Courier* courier, Route const& route);
    void assignCourierPackages(Courier* courier, std::vector<AbstractPackage*> const& packages);
    bool isAvailable(Courier* c);
    std::vector<Courier*> assignUnhandledPackages();

    size_t numOfUnhandledPackages();

    ~Interface(){
        for(auto c:couriers)
            delete c.second;
        unhandledPackages.clear();
        packagesArchive.clear();
        for(auto p:packages)
            delete p.second;
    }
};