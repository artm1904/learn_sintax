#Начиная с версии 3.28, CMake имеет встроенную, стабильную и кросс-платформенную поддержку модулей C++20

cmake_minimum_required(VERSION 3.28)

# Создаем статическую библиотеку для нашего модуля 'math'.
add_library(math_module )

# Добавляем исходный файл модуля в библиотеку.
# PUBLIC означает, что math.cppm является частью публичного интерфейса.
# FILE_SET с типом CXX_MODULES - Мы явно указываем CMake, что файлы в этом наборе являются интерфейсами 
# модулей C++. Это включает механизм сканирования зависимостей.
target_sources(math_module
    PUBLIC
    FILE_SET CXX_MODULES FILES math.cppm
)

# Создаем цель для нашего исполняемого файла
add_executable(moduxe_executable main.cpp)

# Связываем нашу программу с модулем.
# CMake сам позаботится о правильном порядке компиляции:
# сначала будет собран модуль math_module, а затем popcorn_app.
target_link_libraries(moduxe_executable PRIVATE math_module)

