#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <utility>
#include <sstream>
#include "../src/logic/Interface/Interface.h"


class InterfaceTest: public ::testing::Test {
    protected:
    typedef std::unordered_map<std::string, Dimensions*> Sizes;
    Sizes packageDimensions = {
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    };
    Sizes courierCapacities = {
        {"small", new Dimensions(100)},
        {"middle", new Dimensions(200)},
        {"big", new Dimensions(300)},
    };
    Map mp;
    Interface interface;
    virtual void SetUp(){
        std::stringstream ss;
        std::string input = "7 18"
                            "WAW BDG LODZ GD KR POZ KAT "
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
                            "KR LODZ 3 "
                            "KAT KR 2 "
                            "KR KAT 2";
        ss << input;
        ss >> mp;
    }
    virtual void TearDown(){
        for(auto p:packageDimensions)
            delete p.second;
        for(auto c:courierCapacities)
            delete c.second;
    }
};

TEST_F(InterfaceTest, test_creating_interface){
    ASSERT_NO_THROW({Interface interface({
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    }, {
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    }, &mp);});
}
TEST_F(InterfaceTest, test_adding_courier_to_interface){
    Interface emptyInterface = Interface({
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    }, {
        {"small", new Dimensions(100)},
        {"middle", new Dimensions(200)},
        {"big", new Dimensions(300)},
    }, &mp);
    auto courier = emptyInterface.courierFactory.createCourier("test", "WAW", "small", "WAW");
    emptyInterface.addCourier(courier);
    auto id = courier->getID();
    auto returnedCourier = emptyInterface.getCourier(id);
    ASSERT_EQ(returnedCourier, courier);
}
TEST_F(InterfaceTest, test_adding_package_to_interface){
    Interface emptyInterface = Interface({
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    }, {
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    }, &mp);
    auto package = emptyInterface.packageFactory.createPackage("WAW", "POZ", "small", 1, "test");
    emptyInterface.addPackage(package);
    auto id = package->getID();
    auto returnedPackage = emptyInterface.getPackage(id);
    ASSERT_EQ(returnedPackage, package);
}
TEST_F(InterfaceTest, test_setting_courier_route){
    Interface interface = Interface({
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    }, {
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    }, &mp);
    interface.addCourier(interface.courierFactory.createCourier("test", "WAW", "small", "WAW"));
    interface.addCourier(interface.courierFactory.createCourier("test", "POZ", "middle", "POZ"));
    interface.addCourier(interface.courierFactory.createCourier("test", "KR", "big", "KR"));
    interface.addCourier(interface.courierFactory.createCourier("test", "BDG", "small", "BDG"));
    interface.addCourier(interface.courierFactory.createCourier("test", "GD", "big", "GD"));
    interface.addCourier(interface.courierFactory.createCourier("test", "LODZ", "big", "LODZ"));

    interface.addPackage(interface.packageFactory.createPackage("POZ","KR", "small", 1, "test"));
    interface.addPackage(interface.packageFactory.createPackage("WAW","KR", "small", 1, "test"));
    interface.addPackage(interface.packageFactory.createPackage("POZ","WAW", "small", 1, "test"));
    interface.addPackage(interface.packageFactory.createPackage("KAT","WAW", "big", 1, "test"));
    auto courier = interface.courierFactory.createCourier("test", "POZ", "big", "POZ");
    interface.addCourier(courier);
    ASSERT_TRUE(interface.isAvailable(courier));
    auto path = mp.getShortestPath("POZ", "KR").second;
    interface.setCourierNewRoute(courier, path);
    ASSERT_FALSE(interface.isAvailable(courier));
    ASSERT_EQ(courier->getDestination()->getName(), "KR");
    ASSERT_EQ(courier->getNextTravelsal()->getName(), "WAW");
}

TEST_F(InterfaceTest, test_assining_unhandled_packages_number){
    Interface interface = Interface({
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    }, {
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    }, &mp);
    interface.addCourier(interface.courierFactory.createCourier("test", "WAW", "small", "WAW"));
    interface.addCourier(interface.courierFactory.createCourier("test", "POZ", "middle", "POZ"));
    interface.addCourier(interface.courierFactory.createCourier("test", "KR", "big", "KR"));
    interface.addCourier(interface.courierFactory.createCourier("test", "BDG", "small", "BDG"));
    interface.addCourier(interface.courierFactory.createCourier("test", "GD", "big", "GD"));
    interface.addCourier(interface.courierFactory.createCourier("test", "LODZ", "big", "LODZ"));

    interface.addPackage(interface.packageFactory.createPackage("POZ","KR", "small", 1, "test"));
    interface.addPackage(interface.packageFactory.createPackage("WAW","KR", "small", 1, "test"));
    interface.addPackage(interface.packageFactory.createPackage("POZ","WAW", "small", 1, "test"));
    interface.addPackage(interface.packageFactory.createPackage("KAT","WAW", "big", 1, "test"));
    auto courier = interface.courierFactory.createCourier("test", "POZ", "big", "POZ");
    ASSERT_EQ(interface.numOfUnhandledPackages(), 4);
    interface.assignUnhandledPackages();
    ASSERT_EQ(interface.numOfUnhandledPackages(), 0);
}
