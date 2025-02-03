#pragma once
#include <optional>
#include <memory>
#include <vector>
#include <sstream>
#include <unordered_set>
class Iprinter
{
public:
    virtual void print(const std::vector<int> &) = 0;
    virtual std::size_t get_dict_size() = 0;
    virtual std::vector<char> get_dict() = 0;
    virtual ~Iprinter() = default;
};

class alphabet_printer : public Iprinter
{
public:
    alphabet_printer(std::unordered_set<char> alphabet) : dict{alphabet.begin(), alphabet.end()} {}
    void print(const std::vector<int> &sequence)
    {
        std::ostringstream buffer;
        for(const auto &i:sequence)
        {
            buffer<<dict[i];
        }
        buffer << "\n";
        std::fwrite(buffer.str().c_str(), 1, buffer.str().size(), stdout);
    }
    std::size_t get_dict_size()
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
    return std::make_unique<alphabet_printer>(std::unordered_set<char>{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'});
}