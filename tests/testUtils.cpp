// #include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <utility>
#include <sstream>
#include "../src/logic/Utils/Dimensions.h"

class DimensionTest : public ::testing::Test
{
    protected:
    double smallVal=10;
    double bigVal = 100;
    Dimensions* smallVolume;
    Dimensions* bigVolume;
    std::vector<Dimensions*> dimensionsCollection;
    std::vector<double> volumes{1,2,3,4,5,6,7,8,9};
    double totalCollectionVolume=0;
    virtual void SetUp()
    {
        smallVolume = new Dimensions(smallVal);
        bigVolume = new Dimensions(bigVal);
        for(auto v:volumes){
            dimensionsCollection.push_back(new Dimensions(v));
            totalCollectionVolume+=v;
        }

    }
    virtual void TearDown(){
        delete smallVolume;
        delete bigVolume;
        for(auto d:dimensionsCollection)
            delete d;
    }
};

TEST_F(DimensionTest, test_creating_dimension){
    Dimensions d(10);
    ASSERT_DOUBLE_EQ(d.getVolume(), 10);
    Dimensions d2(2,3,4);
    ASSERT_DOUBLE_EQ(d2.getVolume(), 24);
}

TEST_F(DimensionTest, test_comparing_dimensions){
    Dimensions d(smallVal);
    ASSERT_EQ(d, *smallVolume);
    ASSERT_TRUE(*smallVolume!=*bigVolume);
    ASSERT_LT(*smallVolume, *bigVolume);
    ASSERT_GT(*bigVolume, *smallVolume);
    ASSERT_EQ(*smallVolume, *smallVolume);
}

TEST_F(DimensionTest, test_adding_dimensions){
    Dimensions d = *smallVolume+*bigVolume;
    ASSERT_DOUBLE_EQ(d.getVolume(), smallVolume->getVolume()+bigVolume->getVolume());
}

TEST_F(DimensionTest, test_adding_dimensions_collection){
    Dimensions d;
    for(auto dim:dimensionsCollection)
        d+=*dim;
    ASSERT_DOUBLE_EQ(d.getVolume(), totalCollectionVolume);
}



