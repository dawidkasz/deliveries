#include <vector>
#include <memory>
#include "../Package/AbstractPackage.h"

class Courier{
    static size_t number_of_couriers;
    size_t id;
    std::string name;
    City* currentLocalization;
    City* currentDestination=nullptr;
    std::vector<City* > currentRoute;
    City* defaultLocalization;
    Dimensions* capacity;
    size_t timeOfReaching=0;
    std::vector<AbstractPackage*> packages;
    std::vector<Privelages*> privelages;
    public:
    Courier()=default;
    Courier(std::string name, City* defaultLocalization, Dimensions* capacity, std::vector<Privelages*> privelages,City* currentLocalization=nullptr)
    :name(name), defaultLocalization(defaultLocalization), capacity(capacity),currentLocalization(currentLocalization){
        for(auto p:privelages)
            this->privelages.push_back(p);
    };
    bool operator==(Courier const& courier) const;
    bool operator!=(Courier const& courier) const;
    size_t getID() const;
    void addPackages(std::vector<AbstractPackage*> & packages);
    void removeLocalPackages();
    bool canDeliverPackage(AbstractPackage const& package) const;
    void nextLocaction();
    void setNewRoute(std::vector<City* > route);
    size_t getReachTime() const;
    City* getDestination() const;
    City* getCurrentLocation() const;
};