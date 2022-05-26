#include <algorithm>
#include <queue>
#include "limits.h"
#include "Map.h"


City* Map::addCity(std::string name){
    cities[name] = std::make_unique<City> (City(name));
    return cities[name].get();
}

City* Map::getCity(std::string name){
    return cities[name].get();
}


Edge* Map::addEdge(std::string srcCity, std::string dstCity, size_t distance){
    City* cityA = cities[srcCity].get();
    City* cityB = cities[dstCity].get();

    edges.push_back(std::make_unique<Edge> (Edge(cityA, cityB, distance)));
    Edge* edge = edges.back().get();

    cityA->addEdgeFrom(edge);
    cityB->addEdgeTo(edge);
    return edge;
}


void Map::removeEdge(Edge* edge){
    auto it = edges.begin();
    while(it != edges.end()){
        if((*it).get() == edge)
            break;
        ++it;
    }

    City* src = (*it)->getSrc();
    City* dst = (*it)->getDst();

    src->removeEdgeFrom(edge);
    dst->removeEdgeTo(edge);
    edges.erase(it);
}


void Map::removeCity(City* city){
    for(Edge* e : city->getEdgesFrom())
        removeEdge(e);
    for(Edge* e : city->getEdgesTo())
        removeEdge(e);

    cities.erase(city->getName());
}


void Map::removeCity(std::string name){
    removeCity(cities[name].get());
}


std::unordered_map<std::string, std::unique_ptr<City>>::iterator Map::begin(){
    return cities.begin();
}


std::unordered_map<std::string, std::unique_ptr<City>>::iterator Map::end(){
    return cities.end();
}


std::pair<size_t, std::vector<Edge*>> Map::getShortestPath(City*source, City* destination){
    std::unordered_map<City*, size_t> dist;
    std::unordered_map<City*, bool> processed;
    std::unordered_map<City*, Edge*> predecessor;
    std::priority_queue<pairDistCity, std::vector<pairDistCity>, std::greater<pairDistCity>> pq;

    for(auto& it : cities)
        dist[it.second.get()] = ULONG_MAX;
    dist[source] = 0;
    predecessor[source] = nullptr;
    pq.push({0, source});

    while(!pq.empty()){
        pairDistCity p = pq.top();
        pq.pop();

        if(p.second == destination) break;
        if(processed[p.second]) continue;
        processed[p.second] = true;

        for(auto edge : p.second->getEdgesFrom()){
            size_t potentialDist = dist[p.second] + edge->getDist();

            if(potentialDist < dist[edge->getDst()]){
                predecessor[edge->getDst()] = edge;
                dist[edge->getDst()] = potentialDist;
                pq.push({potentialDist, edge->getDst()});
            }
        }
    }

    std::vector<Edge*> path;
    City* curr = destination;
    while(predecessor[curr]){
        path.push_back(predecessor[curr]);
        curr = predecessor[curr]->getSrc();
    }

    std::reverse(path.begin(), path.end());
    return {dist[destination], path};
}


std::pair<size_t, std::vector<Edge*>> Map::getShortestPath(std::string source, std::string destination){
    return getShortestPath(cities[source].get(), cities[destination].get());
}


std::ostream& operator<<(std::ostream& os, Map& map){
    os << map.cities.size() << " " << map.edges.size() << "\n";
    for(auto& it : map)
        os << it.first << " ";
    os << "\n";

    for(auto& e : map.edges)
        os << *e;

    return os;
}


std::istream& operator>>(std::istream& is, Map& map){
    size_t numCities, numEdges;
    is >> numCities >> numEdges;

    for(int i=0; i<numCities; ++i){
        std::string name;
        is >> name;
        map.addCity(name);
    }

    for(int i=0; i<numEdges; ++i){
        std::string name1, name2;
        size_t dist;
        is >> name1 >> name2 >> dist;
        map.addEdge(name1, name2, dist);
    }

    return is;
}
