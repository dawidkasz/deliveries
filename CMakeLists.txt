cmake_minimum_required(VERSION 3.11.0)
project(Spedycja VERSION 0.1.0)

include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES
   src/app/CommandInterpreter/CommandInterpreter.cpp
   src/app/CommandInterpreter/CommandInterpreter.h
   src/logic/Courier/Courier.cpp
   src/logic/Courier/Courier.h
   src/logic/Interface/Interface.cpp
   src/logic/Interface/Interface.h
   src/logic/Package/Package.cpp
   src/logic/Package/Package.h
   src/map/Map/Map.cpp
   src/map/Map/Map.h
   src/map/City/City.cpp
   src/map/City/City.h
   src/map/Edge/Edge.cpp
   src/map/Edge/Edge.h)

add_executable(symulationApp src/app/SymulationApp.cpp ${PROJECT_SOURCES})

add_executable(testSomething tests/SomeUnitTest.cpp ${PROJECT_SOURCES})
target_link_libraries(testSomething PUBLIC gtest_main)