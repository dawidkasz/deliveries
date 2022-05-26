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
    std::vector<Edge*> edgesFrom;
    std::vector<Edge*> edgesTo;
public:
    City(std::string cityCodeName) : name(cityCodeName) {}

    std::string getName() const;

    std::vector<Edge*> getEdgesFrom() const;
    std::vector<Edge*> getEdgesTo() const;

    void addEdgeFrom(Edge* edge);
    void addEdgeTo(Edge* edge);

    void removeEdgeFrom(Edge* edge);
    void removeEdgeTo(Edge* edge);

    std::vector<Edge*>::iterator begin();
    std::vector<Edge*>::iterator end();
};


std::ostream& operator<<(std::ostream& os, City const& city);
