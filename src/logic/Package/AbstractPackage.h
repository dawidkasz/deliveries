#pragma once
#include <string>
#include <memory>
#include "../Utils/Dimensions.h"
#include "../Utils/Privelages.h"
#include "../../map/City/City.h"

enum class Status{ParcelPosted, InTransit, Delivered};

class AbstractPackage{
    static size_t number_of_packages;
    std::string description="";
    size_t id;
    Status status;
    int priority=0;
    Dimensions* dimensions;
    City* source;
    City* destination;
    public:
    AbstractPackage() = default;
    AbstractPackage(std::string description, int priority, Dimensions* dimensions, City* source, City* destination)
    :description(description), priority(priority), dimensions(dimensions), source(source), destination(destination), id(++number_of_packages),
    status(Status::ParcelPosted){};
    virtual int getPriority() = 0;
    virtual std::vector<Privelages*> getPrivelages() = 0;
    virtual void print(std::ostream& c0) const = 0;
    friend  std::ostream& operator<<(std::ostream& c, AbstractPackage const& package){
        package.print(c);
        return c;
    }
    City* getSource(){
        return source;
    }
    City* getDestination(){
        return destination;
    }
    size_t getID(){
        return id;
    }
    Status getStatus(){
        return status;
    }

};