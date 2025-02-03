#include <iostream>
#include <numeric>
#include <vector>
#include "printer.hpp"
#include <chrono>
std::vector<char> generate_alphabet(std::vector<char> origin, std::size_t num_of_copy)
{
    std::vector<char> result;
    for(auto i{0}; i<num_of_copy; i++)
    {
        for(auto j:origin)
        {
            result.push_back(j);
        }
    }
    return result;
}

template <typename T>
void print_sum(T container)
{
    auto sum = std::accumulate(container.begin(), container.end(), 0);
    std::cout<<sum<<" <-side effect\n";
}

int main()
{
    std::vector<char> alphabet = generate_alphabet({'A', 'B', 'C', 'D', 'E', 'F'}, 1000);

    auto start = std::chrono::steady_clock::now();
    alphabet_printer_vector apv{std::vector<char>(alphabet.begin(), alphabet.end())};
    auto stop = std::chrono::steady_clock::now();
    print_sum(apv.get_dict());
    auto vector_delta = stop - start;
    std::cout<<vector_delta.count()<<" vector time \n";

    start = std::chrono::steady_clock::now();
    alphabet_printer standard_printer{std::set<char>(alphabet.begin(), alphabet.end())};
    stop = std::chrono::steady_clock::now();
    auto standard_delta = stop - start;
    print_sum(standard_printer.get_dict());
    std::cout<<standard_delta.count()<<" set time \n";

    start = std::chrono::steady_clock::now();
    alphabet_printer_unordered printer_unordered{std::unordered_set<char>(alphabet.begin(), alphabet.end())};
    stop = std::chrono::steady_clock::now();
    print_sum(printer_unordered.get_dict());
    auto unordered_delta = stop - start;
    std::cout<<unordered_delta.count()<<" unordered set time \n";

    std::cout<<std::max({vector_delta.count(), standard_delta.count(), unordered_delta.count()})<<" max \n";
    std::cout<<std::min({vector_delta.count(), standard_delta.count(), unordered_delta.count()})<<" min \n";
}