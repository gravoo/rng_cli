#include <algorithm>
#include <array>
#include <chrono>
#include <format>
#include <functional>
#include <gtest/gtest.h>
#include <numeric>
#include <random>
#include <set>
#include <sstream>
#include <stdint.h>
#include <unordered_set>

#include "sequence_generation.h"

using namespace ::testing;
using namespace std::chrono;

using RealMicroSeconds = duration<double, std::micro>;

std::string
generateAlphabet(char from, char to)
{
  std::string result{};
  result.reserve(to - from);
  for (char current = from; current <= to; ++current) {
    result.push_back(current);
  }
  return result;
}

class BenchmarkUnifyingSet : public TestWithParam<std::string>
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

TEST_P(BenchmarkUnifyingSet, bySet)
{
  const std::string& input = GetParam();

  collectMeasurements(1000, [&input] {
    std::set<char> collection;

    for (const char c : input) {
      collection.insert(c);
    }

    return std::string{ collection.begin(), collection.end() };
  });
}

TEST_P(BenchmarkUnifyingSet, byUnorderedSet)
{
  const std::string& input = GetParam();

  collectMeasurements(1000, [&input] {
    std::unordered_set<char> collection;

    for (const char c : input) {
      collection.insert(c);
    }

    return std::string{ collection.begin(), collection.end() };
  });
}

TEST_P(BenchmarkUnifyingSet, stlAlgorithmsOnString)
{

  const std::string& input = GetParam();

  collectMeasurements(1000, [&input] {
    std::string collection = input;

    std::ranges::sort(collection);
    auto splitIt = std::unique(collection.begin(), collection.end());

    collection.erase(splitIt, collection.end());

    return collection;
  });
}

namespace {
const std::string alphabet = generateAlphabet(' ' + 1, 'z');

auto generatedSequences = {
  translateResult(alphabet, generateSequence(1 << 3, alphabet.size())),
  translateResult(alphabet, generateSequence(1 << 4, alphabet.size())),
  translateResult(alphabet, generateSequence(1 << 5, alphabet.size())),
  translateResult(alphabet, generateSequence(1 << 6, alphabet.size())),
  translateResult(alphabet, generateSequence(1 << 7, alphabet.size())),
  translateResult(alphabet, generateSequence(1 << 8, alphabet.size())),
  translateResult(alphabet, generateSequence(1 << 9, alphabet.size())),
  translateResult(alphabet, generateSequence(1 << 10, alphabet.size())),
  translateResult(alphabet, generateSequence(1 << 11, alphabet.size())),
  translateResult(alphabet, generateSequence(1 << 12, alphabet.size())),
  translateResult(alphabet, generateSequence(1 << 13, alphabet.size())),
  translateResult(alphabet, generateSequence(1 << 14, alphabet.size())),
  translateResult(alphabet, generateSequence(1 << 15, alphabet.size())),
  translateResult(alphabet, generateSequence(1 << 16, alphabet.size())),
};
}
INSTANTIATE_TEST_SUITE_P(Common,
                         BenchmarkUnifyingSet,
                         ValuesIn(generatedSequences));
