add_executable(benchmarks)
target_sources(benchmarks
  PUBLIC
  ./sequence_generation.h
  PRIVATE
  ./sequence_generation.cpp
  ./benchmark_sequence_generation.cpp
)
target_compile_features(benchmarks PRIVATE cxx_std_20)
target_link_libraries(benchmarks PRIVATE gtest_main)
