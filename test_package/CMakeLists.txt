cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(data-structure REQUIRED)
find_package(Catch2 REQUIRED)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(TARGET_NAME test)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME}
	data-structure::data-structure
        Catch2::Catch2WithMain
)
