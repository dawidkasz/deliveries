#pragma once
#include <iostream>
#include <stdexcept>

class Dimensions{
    double volume=0;
public:
    Dimensions()=default;
    Dimensions(double volume) : volume(volume){
        if(volume<0)
            throw std::invalid_argument("Volume cannot be less than 0");
    };
    Dimensions(double sideA, double sideB, double sideC) : Dimensions(sideA*sideB*sideC){};
    double getVolume() const{
        return volume;
    }
    bool operator<(Dimensions const& dimension) const{
        return getVolume() < dimension.getVolume();
    }
    bool operator>(Dimensions const& dimension) const{
        return getVolume() > dimension.getVolume();
    }
    bool operator==(Dimensions const& dimension) const{
        return abs(getVolume() - dimension.getVolume()) < 0.0001;
    }
    bool operator!=(Dimensions const& dimension) const{
        return !(*this==dimension);
    }
    void operator+=(Dimensions const& dimension){
        volume+=dimension.getVolume();
    }
    Dimensions operator+(Dimensions const& dimension) const{
        Dimensions temp(*this);
        temp+=dimension;
        return temp;
    }
    void operator-=(Dimensions const& dimension){
        if(*this<dimension)
            throw std::invalid_argument("Cannot subtruct from less dimension");
        volume-=dimension.getVolume();
    }
    Dimensions operator-(Dimensions const& dimension) const{
        Dimensions temp(*this);
        temp-=dimension;
        return temp;
    }
    friend std::ostream& operator<<(std::ostream& c, Dimensions const& d){
        c<<d.getVolume();
        return c;
    }
};