#pragma once
#include <unordered_map>
#include <string_view>
#include <iostream>
#include <set>

class Iprinter
{
public:
    virtual void print(std::size_t val) = 0;
    virtual std::size_t get_range() = 0;
    ~Iprinter() = default;
};

class hex_printer : public Iprinter
{
public:
    hex_printer(std::size_t range) : range(range) {}
    void print(std::size_t val)
    {
        std::cout<<std::hex<<val;
    }
    std::size_t get_range()
    {
        return range;
    }
private:
    std::size_t range{0};
};

class alphabet_printer : public Iprinter
{
public:
    alphabet_printer(std::string_view alphabet)
    {
        auto nr{0};
        for(auto i:remove_duplicates(alphabet))
        {
            dict[nr] = i;
            nr++;
        }
        range = dict.size() - 1;
    }
    void print(std::size_t val)
    {
        std::cout<<dict[val];
    }
    std::size_t get_range()
    {
        return range;
    }
private:
    std::set<char> remove_duplicates(std::string_view s)
    {
        std::set<char> resoult;
        for(const auto &i:s)
        {
            resoult.insert(i);
        }
        return resoult;
    }
    std::unordered_map<std::size_t, char> dict;
    std::size_t range{0};
};