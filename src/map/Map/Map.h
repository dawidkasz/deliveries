#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <utility>
#include "limits.h"
#include "../City/City.h"
#include "../Edge/Edge.h"

typedef std::pair<size_t, City*> pairDistCity;
typedef std::pair<std::unordered_map<City*, size_t>, std::unordered_map<City*, Edge*>> pairDistPredecessor;


class Map{
private:
    std::unordered_map<std::string, std::unique_ptr<City>> cities;
    std::vector<std::unique_ptr<Edge>> edges;

    bool hasCycle(std::vector<Edge*> edges) const;
    std::vector<Edge*> multiFragment(std::vector<Edge*> edges, size_t numOfCities) const;
public:
    City* addCity(std::string name);
    City* getCity(std::string name) const;

    void removeCity(City* city);
    void removeCity(std::string name);

    Edge* addEdge(City* srcCity, City* dstCity, size_t distance);
    Edge* addEdge(std::string srcCity, std::string dstCity, size_t distance);
    void removeEdge(Edge* edge);

    std::unordered_map<std::string, std::unique_ptr<City>>::iterator begin();
    std::unordered_map<std::string, std::unique_ptr<City>>::iterator end();

    pairDistPredecessor getAllDistances(City* source) const;

    std::pair<size_t, std::vector<Edge*>> getShortestPath(City* source, City* destination) const;
    std::pair<size_t, std::vector<Edge*>> getShortestPath(std::string source, std::string destination) const;

    std::vector<Edge*> getOptimalRoute(std::vector<City*> cities, City* source) const;

    friend std::ostream& operator<<(std::ostream& os, Map& map);
};


std::istream& operator>>(std::istream& is, Map& map);
