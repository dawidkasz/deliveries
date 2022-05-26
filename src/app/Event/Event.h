#include <string>
#include "../../logic/Courier/Courier.h"
#include "../../map/City/City.h"

class AbstractEvent
{
    public:
        virtual std::string getStr() const noexcept;
};


class DeliveryEvent : public AbstractEvent
{
    private:
        Courier* courier;
        City* city;
        AbstractPackage* package;
    public:
        DeliveryEvent(Courier* courier, City* city) : courier(courier), city(city) {};
        std::string getStr() const noexcept;
};