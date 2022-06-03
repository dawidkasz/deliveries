#pragma once
#include <string>
#include "../../logic/Courier/Courier.h"
#include "../../map/City/City.h"
#include "../Simulation/Simulation.h"

class Simulation;


class AbstractEvent
{
    protected:
        size_t time;
        Simulation* simulation;
    public:
        AbstractEvent(size_t time, Simulation* simulation) : time(time), simulation(simulation) {};
        virtual std::string what() const noexcept = 0;
        virtual void execute() const = 0;
        bool operator<(const AbstractEvent& other) const
        {
            return time < other.time;
        }
        bool operator>(const AbstractEvent& other) const
        {
            return time > other.time;
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
        std::vector<AbstractPackage*> packages;
    public:
        DeliveryEvent(Simulation* simulation, Courier* courier, City* city, std::vector<AbstractPackage*> packages, size_t time) :
            courier(courier), city(city), packages(packages), AbstractEvent(time, simulation) {};
        std::string what() const noexcept;
        void execute() const;
};

class ArriveAtLocEvent : public AbstractEvent
{
    private:
        Courier* courier;
        City* city;
    public:
        ArriveAtLocEvent(Simulation* simulation, Courier* courier, City* city, size_t time) :
            courier(courier), city(city), AbstractEvent(time, simulation) {};
        std::string what() const noexcept;
        void execute() const;
};

class PickupPackageEvent : public AbstractEvent
{
    private:
        Courier* courier;
        City* city;
        std::vector<AbstractPackage*> packages;
    public:
        PickupPackageEvent(Simulation* simulation, Courier* courier, City* city, std::vector<AbstractPackage*> packages, size_t time) :
            courier(courier), city(city), packages(packages), AbstractEvent(time, simulation) {};
        std::string what() const noexcept;
        void execute() const;
};

class AssignPackagesEvent : public AbstractEvent
{
    public:
        AssignPackagesEvent(Simulation* simulation, size_t time) : AbstractEvent(time, simulation) {}
        std::string what() const noexcept;
        void execute() const;
};