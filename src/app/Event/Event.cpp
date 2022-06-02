#include <string>
#include "Event.h"

std::string DeliveryEvent::getStr() const noexcept
{
    std::string result = "";
    result += "Courier " + courier->getID();
    result += "delivered package" + package->getDescription();
    result += "to city " + city->getName();
    return result;
};