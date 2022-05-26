#include <iostream>

class Dimensions{
    double volume=0;
    public:
    Dimensions()=default;
    Dimensions(double volume):volume(volume){};
    Dimensions(double sideA, double sideB, double sideC):volume(sideA*sideB*sideC){};
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
    friend std::ostream& operator<<(std::ostream& c, Dimensions const& d){
        c<<d.getVolume();
        return c;
    }
};