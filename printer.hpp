#pragma once
#include <unordered_map>
#include <optional>
#include <memory>
#include <iostream>
#include <set>

class Iprinter
{
public:
    virtual void print(std::size_t val) = 0;
    virtual std::size_t get_count_of_marks() = 0;
    virtual ~Iprinter() = default;
};

class hex_printer : public Iprinter
{
public:
    hex_printer() = default;
    void print(std::size_t val)
    {
        std::cout<<std::hex<<val;
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
    alphabet_printer(const std::set<char> &alphabet) : marks_in_alphabet{alphabet.size() - 1}
    {
        auto nr{0};
        for(auto i:alphabet)
        {
            dict[nr] = i;
            nr++;
        }
    }
    void print(std::size_t val)
    {
        std::cout<<dict[val];
    }
    std::size_t get_count_of_marks()
    {
        return marks_in_alphabet;
    }
private:
    std::unordered_map<std::size_t, char> dict;
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