#pragma once
#include <string>
#include "../../logic/Courier/Courier.h"
#include "../../map/City/City.h"

class AbstractEvent
{
    private:
        size_t time;
    public:
        AbstractEvent(size_t time) : time(time) {};
        virtual std::string what() const noexcept = 0;
        virtual void execute() const = 0;
        bool operator<(const AbstractEvent& other) const
        {
            return time<other.time;
        }
        size_t getTime() const
        {
            return time;
        }
};


class DeliveryEvent : public AbstractEvent
{
    private:
        Courier* courier;
        City* city;
        AbstractPackage* package;
    public:
        DeliveryEvent(Courier* courier, City* city, AbstractPackage* package, size_t time) :
            courier(courier), city(city), package(package), AbstractEvent(time) {};
        std::string what() const noexcept;
        void execute() const;
};

class ArriveAtLocEvent : public AbstractEvent
{
    private:
        Courier* courier;
        City* city;
    public:
        ArriveAtLocEvent(Courier* courier, City* city, size_t time) :
            courier(courier), city(city), AbstractEvent(time) {};
        std::string what() const noexcept;
        void execute() const;
};

class PickupPackageEvent : public AbstractEvent
{
    private:
        Courier* courier;
        City* city;
        AbstractPackage* package;
    public:
        PickupPackageEvent(Courier* courier, City* city, AbstractPackage* package, size_t time) :
            courier(courier), city(city), package(package), AbstractEvent(time) {};
        std::string what() const noexcept;
        void execute() const;
};