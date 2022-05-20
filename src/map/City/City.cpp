#include "City.h"


std::string City::getName() const{
    return name;
}


std::vector<std::shared_ptr<Edge>> City::getEdgesFrom() const{
    return edgesFrom;
}


std::vector<std::shared_ptr<Edge>> City::getEdgesTo() const{
    return edgesTo;
}


void City::addEdgeFrom(std::shared_ptr<Edge> edge){
    edgesFrom.push_back(edge);
}


void City::addEdgeTo(std::shared_ptr<Edge> edge){
    edgesTo.push_back(edge);
}


void City::removeEdgeFrom(std::shared_ptr<Edge> edge){
    edgesFrom.erase(std::find(edgesFrom.begin(), edgesFrom.end(), edge));
}


void City::removeEdgeTo(std::shared_ptr<Edge> edge){
    edgesTo.erase(std::find(edgesTo.begin(), edgesTo.end(), edge));
}


std::ostream& operator<<(std::ostream& os, City const& city){
    os << city.getName();
    return os;
}


std::vector<std::shared_ptr<Edge>>::iterator City::begin(){
    return edgesFrom.begin();
}


std::vector<std::shared_ptr<Edge>>::iterator City::end(){
    return edgesFrom.end();
}
