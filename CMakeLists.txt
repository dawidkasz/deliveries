cmake_minimum_required(VERSION 3.11.0)
project(Deliveries VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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
   src/app/Command/Command.cpp
   src/app/Command/Command.h
   src/app/Event/Event.cpp
   src/app/Event/Event.h
   src/app/Simulation/Simulation.cpp
   src/app/Simulation/Simulation.h
   src/logic/Courier/Courier.cpp
   src/logic/Courier/Courier.h
   src/logic/Interface/Interface.cpp
   src/logic/Interface/Interface.h
   src/logic/Interface/INotify.h
   src/logic/Package/Package.cpp
   src/logic/Package/Package.h
   src/logic/Package/AbstractPackage.h
   src/logic/Package/PackageFactory.h
   src/logic/Courier/CourierFactory.h
   src/logic/Utils/Dimensions.h
   src/map/Map/Map.cpp
   src/map/Map/Map.h
   src/map/City/City.cpp
   src/map/City/City.h
   src/map/Edge/Edge.cpp
   src/map/Edge/Edge.h)

add_executable(simulationApp src/app/SimulationApp.cpp ${PROJECT_SOURCES})

add_executable(testProgramObjects tests/testPackages.cpp tests/testCouriers.cpp tests/testUtils.cpp ${PROJECT_SOURCES})
add_executable(testInterface tests/testInterface.cpp ${PROJECT_SOURCES})
add_executable(testMap tests/testMap.cpp ${PROJECT_SOURCES})

target_link_libraries(testProgramObjects PUBLIC gtest_main)
target_link_libraries(testInterface PUBLIC gtest_main)
target_link_libraries(testMap PUBLIC gtest_main)
