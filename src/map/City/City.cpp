#include "City.h"


std::string City::getName() const{
    return name;
}


std::vector<Edge*> City::getEdgesFrom() const{
    return edgesFrom;
}


std::vector<Edge*> City::getEdgesTo() const{
    return edgesTo;
}


void City::addEdgeFrom(Edge* edge){
    edgesFrom.push_back(edge);
}


void City::addEdgeTo(Edge* edge){
    edgesTo.push_back(edge);
}


void City::removeEdgeFrom(Edge* edge){
    edgesFrom.erase(std::find(edgesFrom.begin(), edgesFrom.end(), edge));
}


void City::removeEdgeTo(Edge* edge){
    edgesTo.erase(std::find(edgesTo.begin(), edgesTo.end(), edge));
}


std::ostream& operator<<(std::ostream& os, City const& city){
    os << city.getName();
    return os;
}


std::vector<Edge*>::iterator City::begin(){
    return edgesFrom.begin();
}


std::vector<Edge*>::iterator City::end(){
    return edgesFrom.end();
}
