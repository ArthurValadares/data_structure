cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(data-structure CONFIG REQUIRED)

add_executable(example src/main.cpp)
target_link_libraries(example data-structure::data-structure)
