// #include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <utility>
#include <sstream>
#include "../src/logic/Courier/Courier.h"
#include "../src/logic/Package/Package.h"
#include "../src/map/Map/Map.h"

class CourierTest : public ::testing::Test
{
    protected:
    City* city1;
    City* city2;
    Dimensions* capacity;
    Dimensions* smallVolume;
    std::vector<Privelages*> privelages;
    Courier* courier;
    std::vector<AbstractPackage*> packages;
    Dimensions packagesLoad;
    virtual void SetUp()
    {
        courier = new Courier("Test", city1, capacity, privelages, city2);
        city1 = new City("WAW");
        city2 = new City("POZ");
        capacity = new Dimensions(100);
        smallVolume = new Dimensions(10);
        privelages = {
            new Privelages("test1"),
            new Privelages("test2"),
            new Privelages("test3"),
        };
        packages = {
            new Package("test", 10, smallVolume, city1, city2),
            new Package("test", 10, smallVolume, city1, city2),
            new Package("test", 10, smallVolume, city1, city2),
            new Package("test", 10, smallVolume, city1, city2),
        };
        for(auto p:packages)
            packagesLoad+=*p->getVolume();

    }
    virtual void TearDown(){
        delete city1;
        delete city2;
        delete capacity;
        delete smallVolume;
        delete courier;
        for(auto p:privelages)
            delete p;
    }
};

TEST_F(CourierTest, test_creating_courier){
    Courier c("Test", city1, capacity, privelages, city2);
    ASSERT_EQ(c.getCurrentLocation()->getName(), city2->getName());
}

TEST_F(CourierTest, test_assigning_packages){
    ASSERT_NO_THROW(courier->addPackagesToCollect(packages));
}

TEST_F(CourierTest, test_collecting_packages){
    courier->addPackagesToCollect(packages);
    courier->performLocalActions();
    ASSERT_EQ(courier->getCurrentLoad(), packagesLoad);
}

TEST_F(CourierTest, test_comparing_couriers){
    Courier c("Test", city1, capacity, privelages, city2);
    Courier c2("Test", city2, capacity, privelages, city1);
    Courier c3("Test", city1, capacity, privelages, city2);
    ASSERT_TRUE(c==c);
    ASSERT_TRUE(c!=c3);
    ASSERT_FALSE(c==c2);
}

// TEST_F(PackageTest, test_creating_packages){
//     std::vector<Package> packages;
//     for(int i=0;i<=10;i++){
//         packages.push_back(Package(packageDescription, packagePriority, d, source.get(), destination.get()));
//     }
//     int i=1;
//     for(auto p:packages){
//         std::string id = "p"+std::to_string(++i);
//         ASSERT_EQ(p.getID(), id);
//     }
// }
// TEST_F(PackageTest, test_printing_package){
//     Package p(packageDescription, packagePriority, d, source.get(), destination.get());
//     std::stringstream ss;
//     ss<<"Description"<<packageDescription<<'\n';
//     ss<<"Source"<<source<<'\n';
//     ss<<"Destination"<<destination<<'\n';
//     ss<<"Volume"<<d<<'\n';
//     ss<<"Status"<<"Parcel is posted"<<'\n';
//     std::stringstream ss2;
//     ss2<<p;
//     ASSERT_EQ(ss.str(), ss2.str());
// }

