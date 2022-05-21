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
    friend std::ostream& operator<<(std::ostream& c, Dimensions const& d){
        c<<d.getVolume();
        return c;
    }
};