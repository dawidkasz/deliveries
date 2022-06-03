// #include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <utility>
#include <sstream>
#include "../src/logic/Courier/Courier.h"
#include "../src/logic/Courier/CourierFactory.h"
#include "../src/logic/Package/Package.h"
#include "../src/map/Map/Map.h"

class DummyNotify:public INotify{
    public:
    DummyNotify()=default;
    void notifyPackagesDelivery(std::vector<AbstractPackage*> const& packages){

    }
    void notifyDestinationReaching(Courier* c){}
};

class CourierTest : public ::testing::Test
{

    protected:
    INotify* notifier;
    City* warsaw;
    City* poznan;
    City* krakow;
    Dimensions* capacity;
    Dimensions* smallVolume;
    Dimensions* bigVolume;
    Courier* courier;
    Courier* routingCourier;
    std::vector<AbstractPackage*> packages;
    std::vector<AbstractPackage*> packagesManyCities;
    Dimensions packagesLoad;
    Dimensions packagesManyLoad;
    Map mp;
    std::vector<Edge*> exampleRoute;

    std::unordered_map<std::string, Dimensions*> capacities = {
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    };
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
        notifier = new DummyNotify;
        warsaw = mp.getCity("WAW");
        poznan = mp.getCity("POZ");
        krakow = mp.getCity("KR");
        capacity = new Dimensions(100);
        smallVolume = new Dimensions(10);
        bigVolume = new Dimensions(20);

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
        courier = new Courier("Test", warsaw, capacity, warsaw, notifier);
        routingCourier = new Courier("Test", poznan, capacity, poznan, notifier);
        for(auto p:packages)
            packagesLoad+=*p->getVolume();
        for(auto p:packagesManyCities)
            packagesManyLoad+=*p->getVolume();
        exampleRoute = mp.getShortestPath("POZ", "KR").second;




    }
    virtual void TearDown(){
        delete capacity;
        delete smallVolume;
        delete bigVolume;
        delete courier;
        delete routingCourier;
        delete notifier;
        for(auto s:capacities)
            delete s.second;
        for(auto p:packages)
            delete p;
        for(auto p:packagesManyCities)
            delete p;
    }
};

TEST_F(CourierTest, test_creating_courier){
    Courier c("Test", warsaw, capacity, poznan);
    ASSERT_EQ(c.getCurrentLocation()->getName(), poznan->getName());
}

TEST_F(CourierTest, test_creating_courier_by_factory){
    CourierFactory factory = CourierFactory({
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    }, &mp, notifier);
    auto courier = factory.createCourier("Test", "WAW", "small", "WAW");
    ASSERT_EQ(courier->getCurrentLocation()->getName(), "WAW");
    delete courier;
}

TEST_F(CourierTest, test_creating_courier_by_factory_exceptions){
    CourierFactory factory = CourierFactory({
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    }, &mp, notifier);
    ASSERT_THROW({factory.createCourier("Test", "WW", "small", "WAW");}, InvalidCourierData);
    ASSERT_THROW({factory.createCourier("Test", "WAW", "smal", "WAW");}, InvalidCourierData);
    ASSERT_THROW({factory.createCourier("Test", "WAW", "small", "WW");}, InvalidCourierData);
}

TEST_F(CourierTest, test_comparing_couriers){
    Courier c("Test", warsaw, capacity, poznan);
    Courier c2("Test", poznan, capacity, warsaw);
    Courier c3("Test", warsaw, capacity, poznan);
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
    routingCourier->setNewRoute(exampleRoute);
    ASSERT_EQ(routingCourier->getDestination()->getName(), "KR");
}

TEST_F(CourierTest, test_assigning_new_route_exception){
    ASSERT_THROW({courier->setNewRoute(exampleRoute);}, BadStartingRoutePoint);
}

TEST_F(CourierTest, test_moving_courier_forward){
    routingCourier->setNewRoute(exampleRoute);
    ASSERT_EQ(routingCourier->getCurrentLocation()->getName(), "POZ");
    routingCourier->nextLocation();
    ASSERT_EQ(routingCourier->getCurrentLocation()->getName(), "WAW");
    routingCourier->nextLocation();
    ASSERT_EQ(routingCourier->getCurrentLocation()->getName(), "KR");
}

TEST_F(CourierTest, test_moving_courier_forward_empty_route){
    routingCourier->setNewRoute(exampleRoute);
    routingCourier->nextLocation();
    routingCourier->nextLocation();
    ASSERT_THROW({routingCourier->nextLocation();}, EmptyCourierRoute);
}

TEST_F(CourierTest, test_getting_courier_next_travesal){
    routingCourier->setNewRoute(exampleRoute);
    auto trav = routingCourier->getNextTravelsal();
    ASSERT_EQ(trav->getName(), "WAW");
    routingCourier->nextLocation();
    trav = routingCourier->getNextTravelsal();
    ASSERT_EQ(trav->getName(), "KR");
    routingCourier->nextLocation();
    ASSERT_THROW({routingCourier->nextLocation();}, EmptyCourierRoute);
    ASSERT_THROW({routingCourier->getNextTravelsal();}, EmptyCourierRoute);
}

TEST_F(CourierTest, test_full_courier_work){
    ASSERT_EQ(routingCourier->getCurrentLoad().getVolume(), 0);
    routingCourier->addPackagesToCollect(packagesManyCities);
    routingCourier->setNewRoute(exampleRoute);
    routingCourier->performLocalActions();
    ASSERT_EQ(routingCourier->getCurrentLoad().getVolume(), 20);
    routingCourier->nextLocation();
    routingCourier->performLocalActions();
    ASSERT_EQ(routingCourier->getCurrentLocation()->getName(), "WAW");
    ASSERT_EQ(routingCourier->getCurrentLoad().getVolume(), 50);
    routingCourier->nextLocation();
    routingCourier->performLocalActions();
    ASSERT_EQ(routingCourier->getCurrentLocation()->getName(), "KR");
    ASSERT_EQ(routingCourier->getCurrentLoad().getVolume(), 30);
}
