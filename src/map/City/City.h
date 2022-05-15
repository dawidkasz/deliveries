#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "../Edge/Edge.h"

class Edge;


class City{
public:
    std::string name;
    std::vector<std::shared_ptr<Edge>> edgesFrom;
    std::vector<std::shared_ptr<Edge>> edgesTo;
public:
    City(std::string cityCodeName) : name(cityCodeName) {}

    std::string getName() const;

    std::vector<std::shared_ptr<Edge>> getEdgesFrom() const;
    std::vector<std::shared_ptr<Edge>> getEdgesTo() const;

    void addEdgeFrom(std::shared_ptr<Edge> edge);
    void addEdgeTo(std::shared_ptr<Edge> edge);

    void removeEdgeFrom(std::shared_ptr<Edge> edge);
    void removeEdgeTo(std::shared_ptr<Edge> edge);

    std::vector<std::shared_ptr<Edge>>::iterator begin();
    std::vector<std::shared_ptr<Edge>>::iterator end();
};


std::ostream& operator<<(std::ostream& os, City const& city);
