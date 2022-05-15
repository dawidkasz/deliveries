#include <vector>
#include "../Package/Package.h"

class Courier{
    static size_t number_of_couriers;
    size_t id;
    std::vector<Package*> packages;
    City* currentLocalization;
    std::vector<City*> currentRoute;
    Dimensions* capacity;
    City* defaultLocalization;
    public:
    Courier()=default;
    Courier(City* defaultLocalization, Dimensions* capacity, City* currentLocalization=nullptr)
    :defaultLocalization(defaultLocalization), capacity(capacity), currentLocalization(currentLocalization),
    id(++number_of_couriers){};
};