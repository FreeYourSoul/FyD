add_library(fyd
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
        )
add_library(fys::fyd ALIAS fyd)
target_include_directories(fyd PRIVATE include)
target_compile_definitions(fyd PUBLIC cxx_std_20)
target_link_libraries(fyd PUBLIC fys::fil)
target_link_libraries(fyd PRIVATE curl)

add_executable(cli_fyd src/cli_fyd.cpp)
target_link_libraries(cli_fyd PRIVATE fys::fyd)
