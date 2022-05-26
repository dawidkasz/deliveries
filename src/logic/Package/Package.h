#include <string>
#include "AbstractPackage.h"


class Package: public AbstractPackage{
    static size_t number_of_packages;
    public:
    Package(std::string description, int priority, Dimensions* dimensions, City* source, City* destination)
    :AbstractPackage(description, priority, dimensions, source, destination){
        id = createID();
    }
    // :description(description), dimensions(dimensions), source(source), destination(destination), id(++number_of_packages),
    // status(Status::ParcelPosted){};
    std::string createID(){
        return "p"+std::to_string(++number_of_packages);
    }
    int getPriority() const{return priority;}
    std::vector<Privelages*> getPrivelages() const{return std::vector<Privelages*>();}
};