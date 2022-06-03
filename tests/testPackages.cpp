// #include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <utility>
#include <sstream>
#include "../src/logic/Package/Package.h"
#include "../src/logic/Package/PackageFactory.h"

class PackageTest : public ::testing::Test
{
    protected:
    Dimensions* d = new Dimensions(10);
    std::shared_ptr<City> source = std::make_shared<City> (City("WAW"));
    std::shared_ptr<City> destination = std::make_shared<City> (City("POZ"));
    std::string packageDescription = "test";
    int packagePriority = 10;
    Map mp;
    std::unordered_map<std::string, Dimensions*> sizes = {
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

    }
    virtual void TearDown(){
        delete d;
        for(auto s:sizes)
            delete s.second;
    }
};

TEST_F(PackageTest, test_creating_package){
    Package p(packageDescription, packagePriority, d, source.get(), destination.get());
    ASSERT_EQ(p.getDescription(), packageDescription);
    ASSERT_EQ(p.getPriority(), packagePriority);
    ASSERT_EQ(p.getID(), "p1");
}

TEST_F(PackageTest, test_creating_packages){
    std::vector<Package> packages;
    for(int i=0;i<=10;i++){
        packages.push_back(Package(packageDescription, packagePriority, d, source.get(), destination.get()));
    }
    int i=1;
    for(auto p:packages){
        std::string id = "p"+std::to_string(++i);
        ASSERT_EQ(p.getID(), id);
    }
}
TEST_F(PackageTest, test_printing_package){
    Package p(packageDescription, packagePriority, d, source.get(), destination.get());
    std::stringstream ss;
    ss<<"Description: "<<packageDescription<<'\n';
    ss<<"Source: "<<*source<<'\n';
    ss<<"Destination: "<<*destination<<'\n';
    ss<<"Volume: "<<*d<<'\n';
    ss<<"Status: "<<"Parcel is posted"<<'\n';
    std::stringstream ss2;
    ss2<<p;
    ASSERT_EQ(ss.str(), ss2.str());
}

TEST_F(PackageTest, test_creating_package_by_factory){
    PackageFactory factory = PackageFactory({
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    }, &mp);
    auto package = factory.createPackage("WAW", "KR", "small", 1, "Test");
    ASSERT_EQ(package->getDescription(), "Test");
    ASSERT_EQ(package->getPriority(), 1);
    ASSERT_EQ(package->getSource()->getName(), "WAW");
    ASSERT_EQ(package->getDestination()->getName(), "KR");
    ASSERT_EQ(package->getVolume()->getVolume(), sizes["small"]->getVolume());
    // ASSERT_EQ(p.getID(), "p1");
    delete package;
}

TEST_F(PackageTest, test_creating_package_by_factory_exceptions){
    PackageFactory factory = PackageFactory({
        {"small", new Dimensions(10)},
        {"middle", new Dimensions(20)},
        {"big", new Dimensions(30)},
    }, &mp);
    ASSERT_THROW({ factory.createPackage("WW", "KR", "small", 1, "Test");}, InvalidPackageData);
    ASSERT_THROW({ factory.createPackage("WAW", "KRA", "small", 1, "Test");}, InvalidPackageData);
    ASSERT_THROW({ factory.createPackage("WAW", "KR", "massive", 1, "Test");}, InvalidPackageData);
}