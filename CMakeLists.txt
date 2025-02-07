cmake_minimum_required(VERSION 3.16)
project(rng_cli)
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_Declare(GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850
    SOURCE_DIR ./googletest
    OVERRIDE_FIND_PACKAGE
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(argparse GoogleTest)
add_library(cli_lib STATIC cli_handler.cpp)
target_link_libraries(cli_lib argparse)

add_executable(rng main.cpp)
target_link_libraries(rng cli_lib)
target_compile_features(rng PRIVATE cxx_std_20)

add_executable(print_bench print_bench.cpp)
target_compile_features(print_bench PRIVATE cxx_std_20)

add_executable(set_vs_vector_bench set_vs_vector_bench.cpp)
target_compile_features(set_vs_vector_bench PRIVATE cxx_std_20)

add_subdirectory(benchmarks)
