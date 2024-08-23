cmake_minimum_required(VERSION 3.15)
set(LIB_NAME data-structure)

project(${LIB_NAME} CXX)


set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)


file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${INCLUDE_DIR}/*.h)


add_library(${LIB_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${LIB_NAME} PUBLIC include)

set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")
install(TARGETS ${LIB_NAME})
