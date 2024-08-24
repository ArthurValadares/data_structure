cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(Catch2 3 REQUIRED CONFIG)

set(TEST_EXECUTABLE test_data_structure)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

add_executable(${TEST_EXECUTABLE} ${SOURCES})
target_link_libraries(${TEST_EXECUTABLE}
        Catch2::Catch2WithMain
        data-structure
)