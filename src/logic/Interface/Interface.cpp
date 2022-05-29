#include "Interface.h"


void Interface::addPackage(AbstractPackage* package){
    unhandledPackages.push_back(package);
}

bool Interface::moveCourierForward(Courier* courier){
    try{
        courier->nextLocaction();
    }catch(EmptyCourierRoute const& e){
        return false;
    }
    return true;
}

void Interface::performCourierActions(Courier* courier){
    courier->performLocalActions();
}

void Interface::setCourierNewRoute(Courier* courier, Interface::Route const& route){
    courier->setNewRoute(route);
}

void Interface::assignCourierPackages(Courier* courier, std::vector<AbstractPackage*> const& packages){
    courier->addPackagesToCollect(packages);
}
void Interface::notifyPackagesDelivery(std::vector<AbstractPackage*> const& packages){
    for(auto p:packages)
        packagesArchive.push_back(p);
}