#pragma once
#include <vector>
#include "../Package/AbstractPackage.h"

class INotify {
public:
    virtual void notifyPackagesDelivery(std::vector<AbstractPackage*> const& packages)=0;
};