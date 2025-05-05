add_library(Logic STATIC
        Dispatcher.cpp)

target_include_directories(Logic PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(Logic PRIVATE
        nlohmann_json::nlohmann_json
)