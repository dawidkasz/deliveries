#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <utility>
#include "../City/City.h"
#include "../Edge/Edge.h"

typedef std::pair<size_t, std::shared_ptr<City>> pairDistCity;


class Map{
private:
    std::unordered_map<std::string, std::shared_ptr<City>> cities;
    std::vector<std::shared_ptr<Edge>> edges;
public:
    std::shared_ptr<City> addCity(std::string name);
    std::shared_ptr<City> getCity(std::string name);

    void removeCity(std::shared_ptr<City> city);
    void removeCity(std::string name);

    std::shared_ptr<Edge> addEdge(std::string srcCity, std::string dstCity, size_t distance);
    void removeEdge(std::shared_ptr<Edge> edge);

    std::unordered_map<std::string, std::shared_ptr<City>>::iterator begin();
    std::unordered_map<std::string, std::shared_ptr<City>>::iterator end();

    std::pair<size_t, std::vector<std::shared_ptr<Edge>>> getShortestPath(std::shared_ptr<City> source,
                                                                          std::shared_ptr<City> destination);
    std::pair<size_t, std::vector<std::shared_ptr<Edge>>> getShortestPath(std::string source,
                                                                          std::string destination);

    friend std::ostream& operator<<(std::ostream& os, Map& map);
};


std::istream& operator>>(std::istream& is, Map& map);
