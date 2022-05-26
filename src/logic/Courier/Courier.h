#include <vector>
#include <memory>
#include <algorithm>
#include "../Package/AbstractPackage.h"

class Courier{
    typedef std::unordered_map<std::string, std::vector<AbstractPackage*> > Container;
    static size_t number_of_couriers;
    size_t id;
    std::string name;
    City* currentLocalization;
    City* currentDestination=nullptr;
    std::vector<City* > currentRoute;
    City* defaultLocalization;
    Dimensions* capacity;
    size_t timeOfReaching=0;
    Container packagesToCollect;
    Container packagesToDeliver;
    std::vector<Privelages*> privelages;
    Dimensions currentLoad;
    void removeLocalPackages();
    void collectLocalPackages();
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
    void addPackagesToCollect(std::vector<AbstractPackage*> const& packages);
    void performLocalActions();
    bool canDeliverPackage(AbstractPackage const& package) const;
    void nextLocaction();
    void setNewRoute(std::vector<City* > route);
    size_t getReachTime() const;
    City* getDestination() const;
    City* getCurrentLocation() const;
    Dimensions getCurrentLoad() const;
};