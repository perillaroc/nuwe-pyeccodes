cmake_minimum_required (VERSION 3.8)

project(nuwe-pyeccodes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(NUWE_DATA_ROOT ${PROJECT_SOURCE_DIR}/data)

find_package(EcCodes REQUIRED)

add_subdirectory(src)
add_subdirectory(example)