#include <algorithm>
#include <array>
#include <chrono>
#include <format>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <stdint.h>

#include "sequence_generation.h"

char
simpleCheckSum(const std::string& data)
{
  return std::reduce(data.begin(), data.end(), char{ 0 }, [](char c1, char c2) {
    return c1 ^ c2;
  });
}

std::vector<uint16_t>
generateSequence(std::size_t length)
{
  static std::random_device dev{};
  static std::mt19937 gen{ dev() };
  std::uniform_int_distribution<> dist{ 0, 15 };

  std::vector<uint16_t> result{};
  result.resize(length);

  std::ranges::generate(result, [&dist] { return dist(gen); });
  return result;
}
