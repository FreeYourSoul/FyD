cmake_minimum_required(VERSION 3.17)
project(FyD)

find_package(fil REQUIRED)
find_package(fmt REQUIRED)
find_package(CURL REQUIRED)

add_subdirectory(fyd)

if (BUILD_TESTING)
    add_subdirectory(test)
endif()