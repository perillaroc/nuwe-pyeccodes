cmake_minimum_required (VERSION 3.8)

project(nuwe-pyeccodes)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(EcCodes REQUIRED)

add_subdirectory(src)