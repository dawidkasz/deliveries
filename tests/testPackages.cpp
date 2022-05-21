// #include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <utility>
#include <sstream>
#include "../src/logic/Package/Package.h"

class PackageTest : public ::testing::Test
{
    protected:
    Dimensions* d = new Dimensions(10);
    std::shared_ptr<City> source = std::make_shared<City> (City("WAW"));
    std::shared_ptr<City> destination = std::make_shared<City> (City("POZ"));
    std::string packageDescription = "test";
    int packagePriority = 10;

    virtual void SetUp()
    {

    }
    virtual void TearDown(){
        delete d;
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
    ss<<"Description"<<packageDescription<<'\n';
    ss<<"Source"<<source<<'\n';
    ss<<"Destination"<<destination<<'\n';
    ss<<"Volume"<<d<<'\n';
    ss<<"Status"<<"Parcel is posted"<<'\n';
    std::stringstream ss2;
    ss2<<p;
    ASSERT_EQ(ss.str(), ss2.str());
}

