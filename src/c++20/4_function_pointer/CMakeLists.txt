cmake_minimum_required(VERSION 3.28)

add_library(inputManager_module )


target_sources(inputManager_module
    PUBLIC
    FILE_SET CXX_MODULES FILES inputManager.cppm 
)

add_executable(function_p_executable main.cpp inputManager.cpp)

target_link_libraries(function_p_executable PRIVATE inputManager_module)

