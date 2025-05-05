cmake_minimum_required(VERSION 3.29)

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

FetchContent_Declare(json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

project(airport_simulator)

add_subdirectory(src/Core)
add_subdirectory(src/Logic)
add_subdirectory(src/Persistence)

add_executable(airport_simulator src/main.cpp)
# target_compile_features(airport_simulator PRIVATE cxx_std_17) (выше стандарт 20 required)
target_link_libraries(airport_simulator PRIVATE
        Core
        Logic
        nlohmann_json::nlohmann_json
        # SFML::Graphics (unused for now)
)

