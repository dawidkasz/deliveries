#pragma once
#include <string>
#include "../Utils/Dimensions.h"
#include "../../map/City/City.h"

enum class Status{ParcelPosted, InTransit, Delivered};

class Package{
    static size_t number_of_packages;
    std::string description="";
    size_t id;
    Status status;
    Dimensions* dimensions;
    City* source;
    City* destination;
    public:
    Package() = default;
    Package(std::string description, Dimensions* dimensions, City* source, City* destination)
    :description(description), dimensions(dimensions), source(source), destination(destination), id(++number_of_packages),
    status(Status::ParcelPosted){};

};