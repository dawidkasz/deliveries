#include "../Courier/Courier.h"
#include "../../map/Map/Map.h"
class Interface{
    std::vector<Courier*> couriers;
    std::vector<Package*> unhandledPackages;
    std::vector<Package*> packages;
    Map* map;
    std::vector<Dimensions*> packagesDimension;
    std::vector<Dimensions*> couriersCapacity;

    public:
    Interface()=default;
};