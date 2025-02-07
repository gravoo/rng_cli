#include <algorithm>
#include <array>
#include <chrono>
#include <format>
#include <functional>
#include <gtest/gtest.h>
#include <numeric>
#include <random>
#include <sstream>
#include <stdint.h>

#include "sequence_generation.h"

using namespace ::testing;
using namespace std::chrono;

using RealMicroSeconds = duration<double, std::micro>;

class BenchmarkSequenceGeneration : public TestWithParam<std::vector<uint16_t>>
{
protected:
  void collectMeasurements(std::size_t repetitions,
                           std::function<std::string()> experiment)
  {
    std::vector<RealMicroSeconds> result{};
    result.resize(repetitions);

    std::ranges::generate(result, [&experiment, this] {
      auto start = high_resolution_clock::now();
      auto sequence = experiment();
      auto stop = high_resolution_clock::now();

      m_checkSum = simpleCheckSum(sequence);

      return stop - start;
    });

    m_measurements = std::move(result);
  }

  void summarize(const std::vector<RealMicroSeconds>& measurements)
  {
    if (measurements.empty()) {
      std::cout << "No data collected\n";
      return;
    }

    auto [minIt, maxIt] = std::ranges::minmax_element(measurements);

    RealMicroSeconds average = std::accumulate(measurements.begin(),
                                               measurements.end(),
                                               RealMicroSeconds{}) /
                               static_cast<double>(measurements.size());
    std::cout << std::format("[   DATA   ] Min: {:10.2f}us Max: {:10.2f}us "
                             "Ave: {:10.2f}us CheckSum: 0x{:02x}\n",
                             minIt->count(),
                             maxIt->count(),
                             average.count(),
                             m_checkSum);
  }

  void TearDown() override { summarize(m_measurements); }

  std::vector<RealMicroSeconds> m_measurements{};
  uint16_t m_checkSum{};
};

TEST_P(BenchmarkSequenceGeneration, oStringStreamBased)
{
  const std::vector<uint16_t>& input = GetParam();

  collectMeasurements(100, [&input] {
    std::ostringstream out;

    out << std::hex;
    for (const uint16_t& c : input) {
      out << c;
    }

    return out.str();
  });
}

TEST_P(BenchmarkSequenceGeneration, lookupStringBased)
{
  const std::vector<uint16_t>& input = GetParam();

  collectMeasurements(100, [&input] {
    std::string lookup{ "0123456789abcdef" };
    std::string result{};
    result.reserve(input.size());
    std::ranges::transform(input,
                           std::back_inserter(result),
                           [&lookup](uint16_t value) { return lookup[value]; });

    return result;
  });
}

TEST_P(BenchmarkSequenceGeneration, lookupTableBased)
{
  const std::vector<uint16_t>& input = GetParam();

  collectMeasurements(100, [&input] {
    char lookup[] = { "0123456789abcdef" };
    std::string result{};
    result.reserve(input.size());
    std::ranges::transform(input,
                           std::back_inserter(result),
                           [&lookup](uint16_t value) { return lookup[value]; });

    return result;
  });
}
namespace {
auto generatedSequences = {
  generateSequence(1 << 3),  generateSequence(1 << 4),
  generateSequence(1 << 5),  generateSequence(1 << 6),
  generateSequence(1 << 7),  generateSequence(1 << 8),
  generateSequence(1 << 9),  generateSequence(1 << 10),
  generateSequence(1 << 11), generateSequence(1 << 12),
  generateSequence(1 << 13), generateSequence(1 << 14),
  generateSequence(1 << 15), generateSequence(1 << 16),
};
}

INSTANTIATE_TEST_SUITE_P(Common,
                         BenchmarkSequenceGeneration,
                         ValuesIn(generatedSequences));
