cmake_minimum_required(VERSION 3.16)
project(rng_cli)
include(FetchContent)
FetchContent_Declare(
    argh
    GIT_REPOSITORY https://github.com/adishavit/argh.git
    GIT_TAG        431bf323acd3bb805483491ff277dac5d85772ad
)
FetchContent_MakeAvailable(argh)
add_executable(rng main.cpp)
target_link_libraries(rng argh)