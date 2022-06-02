#pragma once
#include <vector>
#include "../Package/AbstractPackage.h"
class Courier;
class INotify{
    public:
    virtual void notifyPackagesDelivery(std::vector<AbstractPackage*> const& packages)=0;
    virtual void notifyDestinationReaching(Courier* c)=0;
};