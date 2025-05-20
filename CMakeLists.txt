cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

project(airport_simulator)

add_executable(
    airport_simulator
    src/main.cpp
    src/Plane.h
    src/Runway.h
    src/Player.h
    src/Plane.cpp
    src/Airport.h
    src/Level.h
    src/LevelInProgress.h
    src/Game.cpp
)

target_compile_features(airport_simulator PRIVATE cxx_std_17)
target_link_libraries(airport_simulator PRIVATE SFML::Graphics)
