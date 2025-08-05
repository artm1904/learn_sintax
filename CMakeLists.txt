cmake_minimum_required(VERSION 3.28)
project(popcorn VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)








# Устанавливаем опции компилятора для нашего проекта
set(PROJECT_COMPILE_OPTIONS)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -pedantic)
endif()


if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3)
endif()

# Мы можем напрямую добавить поддиректорию, содержащую наш исходный код и цели
add_subdirectory(src)
