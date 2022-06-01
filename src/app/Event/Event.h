#include <string>
#include "../../logic/Courier/Courier.h"
#include "../../map/City/City.h"

class AbstractEvent
{
    private:
        size_t time;
    public:
        virtual std::string what() const noexcept = 0;
        virtual void execute() const noexcept = 0;
        bool operator>(const AbstractEvent& other) const
        {
            return time>other.time;
        }
};


class DeliveryEvent : public AbstractEvent
{
    private:
        Courier* courier;
        City* city;
        AbstractPackage* package;
    public:
        DeliveryEvent(Courier* courier, City* city, AbstractPackage* package) : courier(courier), city(city), package(package) {};
        std::string what() const noexcept;
        void execute() const noexcept;
};

class ArriveAtLocEvent : public AbstractEvent
{
    private:
        Courier* courier;
        City* city;
    public:
        ArriveAtLocEvent(Courier* courier, City* city) : courier(courier), city(city) {};
        std::string what() const noexcept;
        void execute() const noexcept;
};

class PickupPackageEvent : public AbstractEvent
{
    private:
        Courier* courier;
        City* city;
        AbstractPackage* package;
    public:
        PickupPackageEvent(Courier* courier, City* city, AbstractPackage* package) :
        courier(courier), city(city), package(package) {};
        std::string what() const noexcept;
        void execute() const noexcept;
}