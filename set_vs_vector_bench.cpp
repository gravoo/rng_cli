#include <iostream>
#include <numeric>
#include <vector>
#include "printer.hpp"
#include <chrono>
#include <unordered_set>
#include <algorithm>
#include <set>

class alphabet_set_printer : public Iprinter
{
public:
    alphabet_set_printer(std::set<char> alphabet) : dict{alphabet.begin(), alphabet.end()}, marks_in_alphabet{dict.size() - 1}
    {}
    void print(const std::vector<int> &sequence)
    {
        for(const auto &i:sequence)
        {
            std::cout<<dict[i];
        }
        std::cout<<std::endl;
    }
    std::size_t get_count_of_marks()
    {
        return marks_in_alphabet;
    }
    std::vector<char> get_dict()
    {
        return dict;
    }
private:
    std::vector<char> dict;
    std::size_t marks_in_alphabet{0};
};

class alphabet_printer_unordered : public Iprinter
{
public:
    alphabet_printer_unordered(std::unordered_set<char> alphabet) : dict{alphabet.begin(), alphabet.end()}
    {}
    void print(const std::vector<int> &sequence)
    {
        for(const auto &i:sequence)
        {
            std::cout<<dict[i];
        }
        std::cout<<std::endl;
    }
    std::size_t get_count_of_marks()
    {
        return dict.size() - 1;
    }
    std::vector<char> get_dict()
    {
        return dict;
    }
private:
    std::vector<char> dict;
};

class alphabet_printer_vector : public Iprinter
{
public:
    alphabet_printer_vector(std::vector<char> alphabet) : dict(alphabet)
    {
        std::sort(dict.begin(), dict.end());
        auto last = std::unique(dict.begin(), dict.end());
        dict.erase(last, dict.end());
    }
    void print(const std::vector<int> &sequence)
    {
        for(const auto &i:sequence)
        {
            std::cout<<dict[i];
        }
        std::cout<<std::endl;
    }
    std::size_t get_count_of_marks()
    {
        return dict.size() - 1;
    }
    std::vector<char> get_dict()
    {
        return dict;
    }
private:
    std::vector<char> dict;
};

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
    alphabet_set_printer set_printer{std::set<char>(alphabet.begin(), alphabet.end())};
    stop = std::chrono::steady_clock::now();
    auto standard_delta = stop - start;
    print_sum(set_printer.get_dict());
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