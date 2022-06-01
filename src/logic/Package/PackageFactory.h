#pragma once
#include "Package.h"
#include "../../map/Map/Map.h"

class PackageFactory{
    typedef std::unordered_map<std::string, Dimensions*> Sizes;
    Sizes packagesDimension;
    Map* map;
    public:
    PackageFactory()=default;
    PackageFactory(Sizes const& packagesDimension, Map* map):packagesDimension(packagesDimension), map(map){};
    Package* createPackage(std::string sourceCity, std::string destinationCity, std::string size, int priority, std::string description){
        auto source = map->getCity(sourceCity);
        auto destination = map->getCity(destinationCity);
        auto dimmension = packagesDimension[size];
        return new Package(description, priority, dimmension, source, destination);
    }

};