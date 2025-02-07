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
generateSequence(std::size_t length, std::size_t range)
{
  static std::random_device dev{};
  static std::mt19937 gen{ dev() };
  std::uniform_int_distribution<> dist{ 0, static_cast<int>(range - 1) };

  std::vector<uint16_t> result{};
  result.resize(length);

  std::ranges::generate(result, [&dist] { return dist(gen); });
  return result;
}

std::size_t
loopRange(std::size_t value, const std::size_t limit)
{
  if (value < limit) [[likely]] {
    return value;
  }
  return value % limit;
}

std::string
translateResult(const std::string& alphabet, const std::vector<uint16_t>& input)
{
  std::string result{};
  result.reserve(input.size());
  std::ranges::transform(
    input, std::back_inserter(result), [&alphabet](uint16_t value) {
      return alphabet[loopRange(value, alphabet.size())];
    });

  return result;
}
