#include <unordered_map>
#include "../Courier/Courier.h"
#include "../Package/AbstractPackage.h"
#include "../Package/PackageFactory.h"
#include "../../map/Map/Map.h"
#include "INotify.h"
class Interface:public INotify{
    typedef std::pair<size_t, std::vector<Edge*> > Route;
    typedef std::unordered_map<std::string, Dimensions*> Sizes;
    std::unordered_map<size_t, Courier*> couriers;
    std::unordered_map<size_t, AbstractPackage*> packages;
    std::unordered_map<std::string, Dimensions*> couriersCapacity;
    std::vector<AbstractPackage*> unhandledPackages;
    std::vector<AbstractPackage*> packagesArchive;
    protected:
    void notifyPackagesDelivery(std::vector<AbstractPackage*> const& packages);
public:
    PackageFactory packageFactory;
    Interface()=default;
    Interface(Sizes const& packagesDimension, Map* map)
    :packageFactory(PackageFactory(packagesDimension, map)){};
    void addCourier();
    Courier* getCourier();
    AbstractPackage* getPackage();
    void addPackage(AbstractPackage* package);
    bool moveCourierForward(Courier* courier);
    void performCourierActions(Courier* courier);
    void setCourierNewRoute(Courier* courier, Route const& route);
    void assignCourierPackages(Courier* courier, std::vector<AbstractPackage*> const& packages);

    std::vector<Courier*> assignUnhandledPackages();
};