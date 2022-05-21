#pragma once
#include <string>
#include <memory>
#include "../Utils/Dimensions.h"
#include "../Utils/Privelages.h"
#include "../../map/City/City.h"

enum class Status{ParcelPosted, InTransit, Delivered};

class AbstractPackage{
    // static size_t number_of_packages;
    std::string verboseStatus(Status s) const{
    if(s==Status::ParcelPosted)
        return "Parcel is posted";
    if(s==Status::InTransit)
        return "Parcel in transit";
    if(s==Status::Delivered)
        return "Parcel is delivered";
    return "Parcel is in unknown state :)";
    }
    protected:
    std::string description="";
    Status status;
    int priority=0;
    Dimensions* dimensions;
    City* source;
    City* destination;
    public:
    virtual std::string createID()=0;
    std::string id;
    AbstractPackage() = default;
    AbstractPackage(std::string description, int priority, Dimensions* dimensions, City* source, City* destination)
    :description(description), priority(priority), dimensions(dimensions), source(source), destination(destination),
    status(Status::ParcelPosted){};
    virtual int getPriority() const = 0;
    virtual std::vector<Privelages*> getPrivelages() const = 0;
    virtual void print(std::ostream& c) const{
        c<<"Description"<<description<<'\n';
        c<<"Source"<<source<<'\n';
        c<<"Destination"<<destination<<'\n';
        c<<"Volume"<<dimensions<<'\n';
        c<<"Status"<<verboseStatus(status)<<'\n';
    }
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
    std::string getID(){
        return id;
    }
    Status getStatus(){
        return status;
    }
    std::string getDescription(){
        return description;
    }

};