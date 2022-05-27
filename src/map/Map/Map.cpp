#include <algorithm>
#include <queue>
#include <stack>
#include <exception>
#include "limits.h"
#include "Map.h"


City* Map::addCity(std::string name){
    cities[name] = std::make_unique<City> (City(name));
    return getCity(name);
}


City* Map::getCity(std::string name) const{
    if(!cities.count(name))
        throw std::invalid_argument("City doesn't exist.");

    return cities.find(name)->second.get();
}


Edge* Map::addEdge(City* srcCity, City* dstCity, size_t distance){
    edges.push_back(std::make_unique<Edge> (Edge(srcCity, dstCity, distance)));
    Edge* edge = edges.back().get();

    srcCity->addEdgeFrom(edge);
    dstCity->addEdgeTo(edge);
    return edge;
}


Edge* Map::addEdge(std::string srcCity, std::string dstCity, size_t distance){
    City* cityA = getCity(srcCity);
    City* cityB = getCity(dstCity);

    return addEdge(cityA, cityB, distance);
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
    removeCity(getCity(name));
}


std::unordered_map<std::string, std::unique_ptr<City>>::iterator Map::begin(){
    return cities.begin();
}


std::unordered_map<std::string, std::unique_ptr<City>>::iterator Map::end(){
    return cities.end();
}


pairDistPredecessor Map::getAllDistances(City* source) const{
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

    return std::make_pair(dist, predecessor);
}


std::pair<size_t, std::vector<Edge*>> Map::getShortestPath(City*source, City* destination) const{
    pairDistPredecessor allDistances = getAllDistances(source);
    std::unordered_map<City*, size_t> dist = allDistances.first;
    std::unordered_map<City*, Edge*> predecessor = allDistances.second;

    std::vector<Edge*> path;
    City* curr = destination;
    while(predecessor[curr]){
        path.push_back(predecessor[curr]);
        curr = predecessor[curr]->getSrc();
    }

    std::reverse(path.begin(), path.end());
    return std::make_pair(dist[destination], path);
}


std::pair<size_t, std::vector<Edge*>> Map::getShortestPath(std::string source, std::string destination) const{
    return getShortestPath(getCity(source), getCity(destination));
}


bool Map::hasCycle(std::vector<Edge*> edges) const{
    std::unordered_map<City*, std::vector<City*>> tmpGraph;
    std::unordered_map<City*, bool> onStack;

    City* start;
    for(Edge* e : edges){
        start = e->getSrc();
        tmpGraph[e->getSrc()].push_back(e->getDst());
    }

    std::stack<City*> st;

    st.push(start);
    onStack[start] = 1;

    while(!st.empty()){
        City* v = st.top();
        st.pop();
        for(City* u: tmpGraph[v]){
            if(onStack[u])
                return true;
            onStack[u] = 1;
            st.push(u);
        }
    }

    return false;
}


std::vector<Edge*> Map::multiFragment(std::vector<Edge*> edges, size_t numOfCities) const{
    sort(edges.begin(), edges.end(), [](Edge* a, Edge* b) { return *a < *b; });

    std::vector<Edge*> tour;
    std::unordered_map<City*, int> inCnt, outCnt;

    for(Edge* e : edges){
        std::vector<Edge*> tmpTour = tour;
        tmpTour.push_back(e);
        bool isClosing = hasCycle(tmpTour);

        if(outCnt[e->getSrc()] == 1 || inCnt[e->getDst()] == 1 || (isClosing && tour.size() < numOfCities))
            continue;

        ++outCnt[e->getSrc()];
        ++inCnt[e->getDst()];

        if(isClosing && tour.size() == numOfCities){
            tour.push_back(e);
            return tour;
        }

        tour.push_back(e);
    }

    return tour;
}


std::vector<Edge*> Map::getOptimalRoute(std::vector<City*> cities, City* source) const{
    if(std::find(cities.begin(), cities.end(), source) == cities.end())
        throw std::invalid_argument("Source not contained in given cities.");

    std::vector<Edge*> tmpMapEdges;
    std::unordered_map<City*, pairDistPredecessor> allPaths;

    for(City* city : cities)
        allPaths[city] = getAllDistances(city);

    for(size_t i=0; i<cities.size(); ++i){
        for(size_t j=i+1; j<cities.size(); ++j){
            tmpMapEdges.push_back(new Edge(cities[i], cities[j], allPaths[cities[i]].first[cities[j]]));
            tmpMapEdges.push_back(new Edge(cities[j], cities[i], allPaths[cities[j]].first[cities[i]]));
        }
    }

    std::vector<Edge*> tour = multiFragment(tmpMapEdges, cities.size());
    std::unordered_map<City*, City*> nextCity;
    std::unordered_map<City*, bool> isNotStart, isNotEnd;
    for(Edge* e : tour){
        if(!isNotStart[e->getSrc()])
            isNotStart[e->getSrc()] = 0;
        isNotStart[e->getDst()] = 1;

        if(!isNotEnd[e->getDst()])
            isNotEnd[e->getDst()] = 0;
        isNotEnd[e->getSrc()] = 1;

        nextCity[e->getSrc()] = e->getDst();
    }

    City* start;
    City* end;
    for(auto it : isNotStart){
        if(!it.second){
            start = it.first;
            break;
        }
    }
    for(auto it : isNotEnd){
        if(!it.second){
            end = it.first;
            break;
        }
    }
    nextCity[end] = start;


    std::vector<City*> tmpRoute;
    std::unordered_map<City*, bool> vis;
    while(!vis[source]){
        vis[source] = true;
        tmpRoute.push_back(source);
        source = nextCity[source];
    }

    std::vector<City*> route = tmpRoute;
    for(int i=tmpRoute.size()-2; i>=0; --i){
        route.push_back(tmpRoute[i]);
    }

    tour.clear();
    for(int i=route.size()-1; i>0; --i){
        std::unordered_map<City*, Edge*> predecessor = allPaths[route[i-1]].second;
        City* curr = route[i];
        std::vector<Edge*> tmpTour = {};
        while(predecessor[curr]){
            tmpTour.push_back(predecessor[curr]);
            curr = predecessor[curr]->getSrc();
        }
        tour.insert(tour.end(), tmpTour.begin(), tmpTour.end());
    }

    std::reverse(tour.begin(), tour.end());

    for(Edge* edge : tmpMapEdges)
        delete edge;
    tmpMapEdges.clear();

    return tour;
}


std::ostream& operator<<(std::ostream& os, Map& map){
    os << map.cities.size() << " " << map.edges.size() << "\n";
    for(auto& it : map)
        os << it.first << " ";
    os << "\n";

    for(auto& e : map.edges)
        os << *e << "\n";

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
