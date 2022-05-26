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
    City* warsaw;
    City* poznan;
    City* krakow;
    Dimensions* capacity;
    Dimensions* smallVolume;
    Dimensions* bigVolume;
    std::vector<Privelages*> privelages;
    Courier* courier;
    Courier* routingCourier;
    std::vector<AbstractPackage*> packages;
    std::vector<AbstractPackage*> packagesManyCities;
    Dimensions packagesLoad;
    Dimensions packagesManyLoad;
    Map mp;
    std::pair<size_t, std::vector<Edge*>> exampleRoute;
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
        exampleRoute = mp.getShortestPath("POZ", "KR");
        warsaw = mp.getCity("WAW");
        poznan = mp.getCity("POZ");
        krakow = mp.getCity("KR");
        capacity = new Dimensions(100);
        smallVolume = new Dimensions(10);
        bigVolume = new Dimensions(20);
        privelages = {
            new Privelages("test1"),
            new Privelages("test2"),
            new Privelages("test3"),
        };
        packagesManyCities = {
            new Package("test", 10, smallVolume, poznan, krakow),
            new Package("test", 10, smallVolume, poznan, warsaw),
            new Package("test", 10, bigVolume, warsaw, poznan),
            new Package("test", 10, smallVolume, krakow, poznan),
            new Package("test", 10, bigVolume, warsaw, krakow),
        };
        packages = {
            new Package("test", 10, smallVolume, warsaw, poznan),
            new Package("test", 10, smallVolume, warsaw, poznan),
            new Package("test", 10, smallVolume, warsaw, poznan),
            new Package("test", 10, smallVolume, warsaw, poznan),
        };
        courier = new Courier("Test", warsaw, capacity, privelages, warsaw);
        routingCourier = new Courier("Test", poznan, capacity, privelages, poznan);
        for(auto p:packages)
            packagesLoad+=*p->getVolume();
        for(auto p:packagesManyCities)
            packagesManyLoad+=*p->getVolume();

    }
    virtual void TearDown(){
        delete capacity;
        delete smallVolume;
        delete bigVolume;
        delete courier;
        delete routingCourier;
        for(auto p:privelages)
            delete p;
    }
};

TEST_F(CourierTest, test_creating_courier){
    Courier c("Test", warsaw, capacity, privelages, poznan);
    ASSERT_EQ(c.getCurrentLocation()->getName(), poznan->getName());
}

TEST_F(CourierTest, test_comparing_couriers){
    Courier c("Test", warsaw, capacity, privelages, poznan);
    Courier c2("Test", poznan, capacity, privelages, warsaw);
    Courier c3("Test", warsaw, capacity, privelages, poznan);
    ASSERT_TRUE(c==c);
    ASSERT_TRUE(c!=c3);
    ASSERT_FALSE(c==c2);
}

TEST_F(CourierTest, test_assigning_packages){
    ASSERT_NO_THROW(courier->addPackagesToCollect(packages));
}

TEST_F(CourierTest, test_collecting_packages){
    courier->addPackagesToCollect(packages);
    courier->performLocalActions();
    ASSERT_EQ(courier->getCurrentLoad(), packagesLoad);
}

TEST_F(CourierTest, test_collecting_packages_but_only_local_one){
    courier->addPackagesToCollect(packagesManyCities);
    courier->performLocalActions();
    ASSERT_EQ(courier->getCurrentLoad().getVolume(), 2*bigVolume->getVolume());
}

TEST_F(CourierTest, test_assigning_new_route){
    courier->setNewRoute(exampleRoute);
    ASSERT_EQ(courier->getDestination()->getName(), "KR");
}

TEST_F(CourierTest, test_moving_courier_forward){
    routingCourier->setNewRoute(exampleRoute);
    ASSERT_EQ(routingCourier->getCurrentLocation()->getName(), "POZ");
    routingCourier->nextLocaction();
    ASSERT_EQ(routingCourier->getCurrentLocation()->getName(), "WAW");
    routingCourier->nextLocaction();
    ASSERT_EQ(routingCourier->getCurrentLocation()->getName(), "KR");
}

TEST_F(CourierTest, test_full_courier_work){
    ASSERT_EQ(routingCourier->getCurrentLoad().getVolume(), 0);
    routingCourier->addPackagesToCollect(packagesManyCities);
    routingCourier->setNewRoute(exampleRoute);
    ASSERT_EQ(routingCourier->getCurrentLoad().getVolume(), 20);
    routingCourier->nextLocaction();
    ASSERT_EQ(routingCourier->getCurrentLocation()->getName(), "WAW");
    ASSERT_EQ(routingCourier->getCurrentLoad().getVolume(), 50);
    routingCourier->nextLocaction();
    ASSERT_EQ(routingCourier->getCurrentLocation()->getName(), "KR");
    ASSERT_EQ(routingCourier->getCurrentLoad().getVolume(), 30);
}
