#pragma once
#include <optional>
#include <memory>
#include <iostream>
#include <set>
#include <vector>

class Iprinter
{
public:
    virtual void print(const std::vector<int> &) = 0;
    virtual std::size_t get_count_of_marks() = 0;
    virtual ~Iprinter() = default;
};

class hex_printer : public Iprinter
{
public:
    hex_printer() = default;
    void print(const std::vector<int> &sequence)
    {
        for(const auto &i:sequence)
        {
            std::cout<<std::hex<<i;
        }
        std::cout<<std::endl;
    }
    std::size_t get_count_of_marks()
    {
        return marks_in_hex;
    }
private:
    std::size_t marks_in_hex{15};
};

class alphabet_printer : public Iprinter
{
public:
    alphabet_printer(const std::set<char> &alphabet) : dict{alphabet.begin(), alphabet.end()}, marks_in_alphabet{dict.size() - 1}
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
private:
    std::vector<char> dict;
    std::size_t marks_in_alphabet{0};
};

std::unique_ptr<Iprinter> printer_factory(std::optional<std::string> alphabet)
{
    if(alphabet)
    {
        return std::make_unique<alphabet_printer>(std::set<char>(alphabet->begin(), alphabet->end()));
    }
    return std::make_unique<hex_printer>();
}