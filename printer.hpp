#pragma once
#include <optional>
#include <memory>
#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <unordered_set>
class Iprinter
{
public:
    virtual void print(const std::vector<int> &) = 0;
    virtual std::size_t get_count_of_marks() = 0;
    virtual std::vector<char> get_dict() = 0;
    virtual ~Iprinter() = default;
};
class hex_printer : public Iprinter
{
public:
    hex_printer() = default;
    void print(const std::vector<int> &sequence)
    {
        std::ostringstream buffer;
        for (const auto &i : sequence) {
            buffer<<hex[i];
        }
        buffer << "\n";
        std::fwrite(buffer.str().c_str(), 1, buffer.str().size(), stdout);
    }
    std::vector<char> get_dict()
    {
        return std::vector<char>{hex.begin(), hex.end()};
    }
    std::size_t get_count_of_marks()
    {
        return hex.size() - 1;
    }
private:
    std::array<char,16> hex{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
};

class alphabet_printer : public Iprinter
{
public:
    alphabet_printer(std::unordered_set<char> alphabet) : dict{alphabet.begin(), alphabet.end()} {}
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

std::unique_ptr<Iprinter> printer_factory(std::optional<std::string> alphabet)
{
    if(alphabet)
    {
        return std::make_unique<alphabet_printer>(std::unordered_set<char>(alphabet->begin(), alphabet->end()));
    }
    return std::make_unique<hex_printer>();
}