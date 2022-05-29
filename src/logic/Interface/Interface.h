#include "../Courier/Courier.h"
#include "../Package/AbstractPackage.h"
#include "../../map/Map/Map.h"
#include "INotify.h"
class Interface:public INotify{
    typedef std::pair<size_t, std::vector<Edge*> > Route;

    std::unordered_map<size_t, Courier*> couriers;
    std::unordered_map<size_t, AbstractPackage*> packages;
    std::unordered_map<std::string, Dimensions*> packagesDimension;
    std::unordered_map<std::string, Dimensions*> couriersCapacity;
    std::vector<AbstractPackage*> unhandledPackages;
    std::vector<AbstractPackage*> packagesArchive;
    protected:
    void notifyPackagesDelivery(std::vector<AbstractPackage*> const& packages);

public:
    Interface()=default;
    void addCourier();
    void addPackage(AbstractPackage* package);
    Courier* getCourier();
    AbstractPackage* getPackage();

    bool moveCourierForward(Courier* courier);
    void performCourierActions(Courier* courier);
    void setCourierNewRoute(Courier* courier, Route const& route);
    void assignCourierPackages(Courier* courier, std::vector<AbstractPackage*> const& packages);

    std::vector<Courier*> assignUnhandledPackages();
};