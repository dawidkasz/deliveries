#pragma once
#include <stdexcept>
#include <unordered_map>
#include "Package.h"
#include "../../map/Map/Map.h"


struct InvalidPackageData : public std::exception
{
    std::string message;
    InvalidPackageData(std::string message):message(message){};
	const char * what () const throw ()
    {
    	return ("Provided package data are invalid:\n"+message).c_str();
    }
};

class PackageFactory{
    typedef std::unordered_map<std::string, Dimensions*> Sizes;
    Sizes packagesDimension;
    Map* map;
public:
    PackageFactory()=default;
    PackageFactory(Sizes const& packagesDimension, Map* map):packagesDimension(packagesDimension), map(map){};
    Package* createPackage(std::string sourceCity, std::string destinationCity, std::string size, int priority, std::string description){
        try{
            auto source = map->getCity(sourceCity);
            auto destination = map->getCity(destinationCity);
            auto dimmension = packagesDimension[size];
            if(dimmension==nullptr)
                throw std::invalid_argument("Provided size doesn't exits!");
            return new Package(description, priority, dimmension, source, destination);
        }
        catch(std::invalid_argument &e){
            throw InvalidPackageData(e.what());
        }
    }
};