#include <string>
#include "Event.h"

std::string DeliveryEvent::what() const noexcept
{
    std::string result = "";
    result += "Courier " + courier->getID();
    result += "delivered package" + package->getDescription();
    result += "to city " + city->getName();
    return result;
};

std::string ArriveAtLocEvent::what() const noexcept
{
    return "";
};

std::string PickupPackageEvent::what() const noexcept
{
    return "";
};

void DeliveryEvent::execute() const
{

}

void ArriveAtLocEvent::execute() const
{

}

void PickupPackageEvent::execute() const
{

}