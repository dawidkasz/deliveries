#pragma once
#include <stdexcept>
#include <unordered_map>
#include "Courier.h"
#include "../../map/Map/Map.h"


struct InvalidCourierData : public std::logic_error
{
    using logic_error::logic_error;
    InvalidCourierData(std::string message) : logic_error("Provided courier data are invalid:\n"+message) {};
};

class CourierFactory {
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
        }
        catch(std::invalid_argument &e){
            throw InvalidCourierData(e.what());
        }
    }

    ~CourierFactory(){
        for(auto c : couriersCapacity)
            delete c.second;
    }
};