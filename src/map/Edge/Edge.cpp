#include "Edge.h"


City* Edge::getSrc() const{
    return src;
}


City* Edge::getDst() const{
    return dst;
}


size_t Edge::getDist() const{
    return dist;
}


void Edge::setDist(size_t newDist){
    dist = newDist;
}

bool Edge::operator<(Edge const& e){
    return dist < e.dist;
}


bool Edge::operator>(Edge const& e){
    return dist > e.dist;
}


std::ostream& operator<<(std::ostream& os, Edge const& edge){
    os << *edge.getSrc() << " " << *edge.getDst() << " " << edge.getDist();
    return os;
}
