#include <gtest/gtest.h>
#include <sstream>
#include <exception>
#include "../src/map/City/City.h"
#include "../src/map/Edge/Edge.h"
#include "../src/map/Map/Map.h"


TEST(testEdge, testGettersAndSetters){
    std::unique_ptr<City> city1 = std::make_unique<City> (City("WAW"));
    std::unique_ptr<City> city2 = std::make_unique<City> (City("POZ"));

    Edge edge(city1.get(), city2.get(), 9);
    edge.setDist(11);

    ASSERT_EQ(edge.getSrc(), city1.get());
    ASSERT_EQ(edge.getDst(), city2.get());
    ASSERT_EQ(edge.getDist(), 11);
    ASSERT_EQ(true, true);
}


TEST(testEdge, testOstream){
    std::unique_ptr<City> city1 = std::make_unique<City> (City("WAW"));
    std::unique_ptr<City> city2 = std::make_unique<City> (City("POZ"));

    Edge edge(city1.get(), city2.get(), 9);
    std::stringstream ss;
    ss << edge;

    ASSERT_EQ(ss.str(), "WAW POZ 9");
}


TEST(testCity, testGettersAndSetters){
    std::unique_ptr<City> city1 = std::make_unique<City> (City("WAW"));
    std::unique_ptr<City> city2 = std::make_unique<City> (City("POZ"));

    std::unique_ptr<Edge> edge = std::make_unique<Edge> (Edge(city1.get(), city2.get(), 5));
    city1->addEdgeFrom(edge.get());
    city2->addEdgeTo(edge.get());

    ASSERT_EQ(city1->getName(), "WAW");
    ASSERT_EQ(city2->getName(), "POZ");
    ASSERT_EQ(city1->getEdgesFrom()[0], edge.get());
    ASSERT_EQ(city2->getEdgesTo()[0], edge.get());

    city1->removeEdgeFrom(edge.get());
    ASSERT_EQ(city1->getEdgesFrom().size(), 0);

    city2->removeEdgeTo(edge.get());
    ASSERT_EQ(city2->getEdgesTo().size(), 0);
}


TEST(testCity, testIterator){
    std::unique_ptr<City> city1 = std::make_unique<City> (City("WAW"));
    std::unique_ptr<City> city2 = std::make_unique<City> (City("POZ"));

    std::unique_ptr<Edge> e1 = std::make_unique<Edge> (Edge(city1.get(), city2.get(), 3));
    std::unique_ptr<Edge> e2 = std::make_unique<Edge> (Edge(city1.get(), city2.get(), 4));
    std::unique_ptr<Edge> e3 = std::make_unique<Edge> (Edge(city1.get(), city2.get(), 5));

    city1->addEdgeFrom(e1.get());
    city1->addEdgeFrom(e2.get());
    city1->addEdgeFrom(e3.get());

    City& city = *city1;
    auto it = city.begin();

    ASSERT_EQ(*it, e1.get());
    ASSERT_EQ(*(++it), e2.get());
    ASSERT_EQ(*(++it), e3.get());
    ASSERT_EQ(*(++it), *city.end());
}


TEST(testCity, testOstream){
    City city("ABCD");
    std::stringstream ss;
    ss << city;

    ASSERT_EQ(ss.str(), "ABCD");
}


TEST(testMap, testIterator){
    Map mp;
    City*  c = mp.addCity("A");
    mp.addCity("B");

    auto it = mp.begin();

    if(it->second.get() == c){
        ASSERT_EQ(it->second->getName(), "A");
        ASSERT_EQ((++it)->second->getName(), "B");
    }else{
        ASSERT_EQ(it->second->getName(), "B");
        ASSERT_EQ((++it)->second->getName(), "A");
    }
}


TEST(testMap, testAdd){
    Map mp;

    City* c = mp.addCity("A");
    mp.addCity("B");
    mp.addCity("C");

    mp.addEdge("A", "B", 5);
    mp.addEdge("B", "A", 4);
    mp.addEdge("A", "C", 3);
    mp.addEdge("C", "B", 2);

    size_t numCities = 0;
    for(auto& it : mp) ++numCities;
    ASSERT_EQ(numCities, 3);

    auto it = c->begin();
    ASSERT_EQ((*it)->getDist(), 5);
    ASSERT_EQ((*++it)->getDist(), 3);
}


TEST(testMap, testAddRemove){
    Map mp;

    City* city = mp.addCity("A");
    mp.addCity("B");
    mp.addCity("C");

    mp.addEdge("A", "B", 5);
    mp.addEdge("B", "A", 4);
    mp.addEdge("A", "C", 3);
    mp.addEdge("C", "B", 2);

    mp.removeCity("C");

    size_t numCities = 0;
    for(auto& it : mp) ++numCities;
    ASSERT_EQ(numCities, 2);

    auto it = city->begin();
    ASSERT_EQ((*it)->getDist(), 5);
    ASSERT_EQ(++it, city->end());
}


TEST(testMap, testGetCity){
    Map mp;
    City* cityA = mp.addCity("A");
    mp.addCity("B");
    mp.addEdge("A", "B", 5);

    ASSERT_EQ(mp.getCity("A"), cityA);
    EXPECT_THROW(mp.getCity("C"), std::invalid_argument);
}


TEST(testMap, testGetShortestPath){
    Map mp;
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

    std::pair<size_t, std::vector<Edge*>> res = mp.getShortestPath("POZ", "KR");
    ASSERT_EQ(res.first, 6);
    ASSERT_EQ(res.second[0]->getSrc()->getName(), "POZ");
    ASSERT_EQ(res.second[0]->getDst()->getName(), "WAW");
    ASSERT_EQ(res.second[1]->getSrc()->getName(), "WAW");
    ASSERT_EQ(res.second[1]->getDst()->getName(), "KR");
}
