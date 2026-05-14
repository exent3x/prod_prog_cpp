cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(PC)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${CMAKE_SOURCE_DIR}/crop_box_filter/crop_box_filter.cpp
)

set(HEADERS
    ${CMAKE_SOURCE_DIR}/filter.hpp
    ${CMAKE_SOURCE_DIR}/Logger.h
    ${CMAKE_SOURCE_DIR}/PointCloud.h
    ${CMAKE_SOURCE_DIR}/crop_box_filter/crop_box_filter.hpp
)

add_executable(PC ${SOURCES} ${HEADERS})
target_include_directories(PC PRIVATE ${CMAKE_SOURCE_DIR})