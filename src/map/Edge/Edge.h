#pragma once
#include <iostream>
#include <memory>
#include "../City/City.h"

class City;


class Edge{
private:
    std::shared_ptr<City> src, dst;
    size_t dist;
public:
    Edge(std::shared_ptr<City> source, std::shared_ptr<City> destination, size_t distance)
        : src(source), dst(destination), dist(distance) {}

    std::shared_ptr<City> getSrc() const;
    std::shared_ptr<City> getDst() const;

    size_t getDist() const;
    void setDist(size_t newDist);
};


std::ostream& operator<<(std::ostream& os, Edge const& edge);
