#pragma once
#include "AbstractPackage.h"
#include <string>


class Package : public AbstractPackage {
    static size_t number_of_packages;
public:
    Package(std::string description, int priority, Dimensions* dimensions, City* source, City* destination)
    :AbstractPackage(description, priority, dimensions, source, destination){
        id = createID();
    }

    std::string createID(){
        return "p"+std::to_string(++number_of_packages);
    }
    int getPriority() const{return priority;}
};