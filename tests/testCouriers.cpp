// #include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <utility>
#include <sstream>
#include "../src/logic/Courier/Courier.h"
#include "../src/logic/Package/Package.h"
#include "../src/map/Map/Map.h"

class PackageTest : public ::testing::Test
{
    protected:
    Dimensions* smallVolume = new Dimensions(10);
    Dimensions* bigVolume = new Dimensions(30);
    Dimensions* smallCapacity = new Dimensions(100);
    Dimensions* bigCapacity = new Dimensions(400);
    Map mp;
    std::shared_ptr<City> city1;
    std::shared_ptr<City> city2;
    std::shared_ptr<City> city3;
    std::shared_ptr<City> city4;
    std::shared_ptr<City> city5;
    std::shared_ptr<City> city6;
    std::string packageDescription = "test";
    int packagePriority = 10;
    std::vector<Privelages*> privelages = {
        new Privelages("test test", 1),
        new Privelages("test test1", 1),
        new Privelages("test test2", 1),
        new Privelages("test test3", 1),
        new Privelages("test test4", 1),
    };
    std::vector<AbstractPackage*> packages;

    virtual void SetUp()
    {
        std::stringstream ss;
        std::string input = "6 16"
                            "WAW BDG LODZ GD KR POZ "
                            "WAW BDG 4 "
                            "BDG WAW 4 "
                            "WAW POZ 3 "
                            "POZ WAW 3 "
                            "WAW LODZ 1 "
                            "LODZ WAW 1 "
                            "WAW KR 3 "
                            "KR WAW 3 "
                            "WAW GD 3 "
                            "GD WAW 3 "
                            "BDG GD 2 "
                            "GD BDG 2 "
                            "BDG POZ 2 "
                            "POZ BDG 2 "
                            "LODZ KR 3 "
                            "KR LODZ 3";
        ss << input;
        ss >> mp;
        city1 = mp.getCity("WAW");
        city2 = mp.getCity("BDG");
        city3 = mp.getCity("LODZ");
        city4 = mp.getCity("GD");
        city5 = mp.getCity("KR");
        city6 = mp.getCity("POZ");

        packages = {
            new Package(packageDescription, packagePriority, smallVolume, city1.get(), city6.get()),
            new Package(packageDescription, packagePriority, smallVolume, city2.get(), city4.get()),
            new Package(packageDescription, packagePriority, smallVolume, city5.get(), city1.get()),
         };

    }
    virtual void TearDown(){
        delete smallVolume;
        delete bigVolume;
        delete smallCapacity;
        delete bigCapacity;
        for(auto p:packages)
            delete p;
        for(auto p:privelages)
            delete p;
    }
};

TEST_F(PackageTest, test_creating_courier){

    Courier c1("Test", city1, privelages, city1);
    Courier c2("Test 2", city2, privelages, city4);
    ASSERT_EQ(c1.getCurrentLocation(), city1);
    ASSERT_EQ(c1.getCurrentLocation(), city4);
    ASSERT_FALSE(c1.getID()==c2.getID());
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

