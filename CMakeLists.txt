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
    src/Player.h
    src/Plane.cpp
    src/Road.cpp
    src/Runway.cpp
    src/Airport.cpp
    src/Level.h
    src/LevelInProgress.cpp
    src/Game.cpp
    src/Camera.h
    src/LevelProducer.h
        src/Menu.cpp
        src/Menu.h
)

target_compile_features(airport_simulator PRIVATE cxx_std_17)
target_link_libraries(airport_simulator PRIVATE SFML::Graphics)
