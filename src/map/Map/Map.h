#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <utility>
#include "../City/City.h"
#include "../Edge/Edge.h"

typedef std::pair<size_t, City*> pairDistCity;


class Map{
private:
    std::unordered_map<std::string, std::unique_ptr<City>> cities;
    std::vector<std::unique_ptr<Edge>> edges;
public:
    City* addCity(std::string name);
    City* getCity(std::string name);

    void removeCity(City* city);
    void removeCity(std::string name);

    Edge* addEdge(std::string srcCity, std::string dstCity, size_t distance);
    void removeEdge(Edge* edge);

    std::unordered_map<std::string, std::unique_ptr<City>>::iterator begin();
    std::unordered_map<std::string, std::unique_ptr<City>>::iterator end();

    std::pair<size_t, std::vector<Edge*>> getShortestPath(City* source, City* destination);
    std::pair<size_t, std::vector<Edge*>> getShortestPath(std::string source, std::string destination);

    friend std::ostream& operator<<(std::ostream& os, Map& map);
};


std::istream& operator>>(std::istream& is, Map& map);
