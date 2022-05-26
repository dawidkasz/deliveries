#pragma once
#include <iostream>
#include <memory>
#include "../City/City.h"

class City;


class Edge{
private:
    City* src;
    City* dst;
    size_t dist;
public:
    Edge(City* source, City* destination, size_t distance)
        : src(source), dst(destination), dist(distance) {}

    City* getSrc() const;
    City* getDst() const;

    size_t getDist() const;
    void setDist(size_t newDist);
};


std::ostream& operator<<(std::ostream& os, Edge const& edge);
