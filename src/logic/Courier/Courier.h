#include <vector>
#include <memory>
#include "../Package/AbstractPackage.h"

class Courier{
    static size_t number_of_couriers;
    size_t id;
    std::string name;
    std::shared_ptr<City> currentLocalization;
    std::shared_ptr<City> currentDestination=nullptr;
    std::vector<std::shared_ptr<City> > currentRoute;
    std::shared_ptr<City> defaultLocalization;
    Dimensions* capacity;
    size_t timeOfReaching=0;
    std::vector<AbstractPackage*> packages;
    std::vector<Privelages*> privelages;
    public:
    Courier()=default;
    Courier(std::string name, std::shared_ptr<City> defaultLocalization, std::vector<Privelages*> privelages, std::shared_ptr<City> currentLocalization=nullptr)
    :name(name), defaultLocalization(defaultLocalization), privelages(privelages), currentLocalization(currentLocalization){};

    size_t getID() const;
    void addPackages(std::vector<AbstractPackage*> & packages);
    void removeLocalPackages();
    bool canDeliverPackage(AbstractPackage const& package) const;
    void nextLocaction();
    void setNewRoute(std::vector<std::shared_ptr<City> > route);
    size_t getReachTime() const;
    std::shared_ptr<City> getDestination() const;
    std::shared_ptr<City> getCurrentLocation() const;
};