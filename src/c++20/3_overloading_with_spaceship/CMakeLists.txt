cmake_minimum_required(VERSION 3.28)




add_library(vector3 STATIC)

target_sources(vector3
    PUBLIC
    FILE_SET CXX_MODULES FILES vector3.cppm
)

add_executable(overloading_with_spaceship main.cpp)

target_link_libraries(overloading_with_spaceship PRIVATE vector3)
