#pragma once
#include <stdexcept>
#include <unordered_map>
#include "Courier.h"
#include "../../map/Map/Map.h"


struct InvalidCourierData : public std::exception
{
    std::string message;
    InvalidCourierData(std::string message):message(message){};
	const char * what () const throw ()
    {
    	return ("Provided courier data are invalid:\n"+message).c_str();
    }
};

class CourierFactory{
    typedef std::unordered_map<std::string, Dimensions*> Sizes;
    Sizes couriersCapacity;
    Map* map;
    INotify* notifier;
    public:
    CourierFactory()=default;
    CourierFactory(Sizes const& couriersCapacity, Map* map, INotify* notifier):couriersCapacity(couriersCapacity), map(map), notifier(notifier){};
    Courier* createCourier(std::string name, std::string defaultLocalization, std::string capacity, std::string currentLocalization){
        try{
        auto defLoc = map->getCity(defaultLocalization);
        auto currLoc = map->getCity(currentLocalization);
        auto courierCapacity = couriersCapacity[capacity];
        if(courierCapacity==nullptr)
            throw std::invalid_argument("Provided size doesn't exits!");
        return new Courier(name, defLoc, courierCapacity, currLoc, notifier);
        }catch(std::invalid_argument &e){
            throw InvalidCourierData(e.what());
        }
    }

};