cmake_minimum_required(VERSION 3.16)
project(rng_cli)
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)
add_executable(rng main.cpp)
target_link_libraries(rng argparse)
target_compile_features(rng PRIVATE cxx_std_20)