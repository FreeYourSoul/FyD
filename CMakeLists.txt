cmake_minimum_required(VERSION 3.17)
project(FyD)

set(CMAKE_CXX_STANDARD 20)

add_executable(FyD
        include/data_types.hh
        include/free_data.hh
        include/data_sources/youtube.hh
        src/data_sources/youtube.cpp
        include/data_sources/twitter.hh
        src/data_sources/youtube.cpp
        include/data_sources/twitch.hh
        src/data_sources/twitch.cpp
        include/free_data.hh
        src/free_data.cpp
        src/cli_fyd.cpp
        )

target_include_directories(FyD PRIVATE include)