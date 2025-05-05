add_library(Core STATIC
        EventQueue.cpp
        LevelManager.cpp
        AirplaneFactory.cpp)

target_include_directories(Core PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(Core PRIVATE
        nlohmann_json::nlohmann_json
)