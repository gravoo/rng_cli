#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include "printer.hpp"
#include "random_seq_generator.hpp"
#include <chrono>

class test_iostream_printer : public Iprinter
{
public:
    test_iostream_printer() = default;
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

class test_lookup_printer : public Iprinter
{
public:
    test_lookup_printer() = default;
    void print(const std::vector<int> &sequence)
    {
        for(const auto &i:sequence)
        {
            std::cout<<hex[i];
        }
        std::cout<<std::endl;
    }
    std::size_t get_count_of_marks()
    {
        return hex.size() - 1;
    }
private:
    std::array<char,16> hex{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
};

class test_ostream_printer : public Iprinter
{
public:
    test_ostream_printer() = default;
    void print(const std::vector<int> &sequence)
    {
        std::cout.setf(std::ios::hex, std::ios::basefield);
        std::copy(sequence.begin(), sequence.end(), std::ostream_iterator<int>(std::cout, ""));
        std::cout.unsetf(std::ios::basefield);
        std::cout<<std::endl;
    }
    std::size_t get_count_of_marks()
    {
        return marks_in_hex;
    }
private:
    std::size_t marks_in_hex{15};
};

class test_fwrite_printer : public Iprinter
{
public:
    test_fwrite_printer() = default;
    void print(const std::vector<int> &sequence)
    {
        std::ostringstream buffer;
        for (const auto &i : sequence) {
            buffer<<std::hex<<i;
        }
        buffer << "\n";
        std::fwrite(buffer.str().c_str(), 1, buffer.str().size(), stdout);
    }
    std::size_t get_count_of_marks()
    {
        return marks_in_hex;
    }
private:
    std::size_t marks_in_hex{15};
};

class test_fwrite_lookup_printer : public Iprinter
{
public:
    test_fwrite_lookup_printer() = default;
    void print(const std::vector<int> &sequence)
    {
        std::ostringstream buffer;
        for (const auto &i : sequence) {
            buffer<<hex[i];
        }
        buffer << "\n";
        std::fwrite(buffer.str().c_str(), 1, buffer.str().size(), stdout);
    }
    std::size_t get_count_of_marks()
    {
        return hex.size() - 1;
    }
private:
    std::array<char,16> hex{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
};

struct Meas
{
    std::chrono::nanoseconds standard;
    std::chrono::nanoseconds lookup;
    std::chrono::nanoseconds ostream;
    std::chrono::nanoseconds fwrite;
    std::chrono::nanoseconds fwrite_lookup;
};

int main(int argc, char **argv)
{
    const auto sequence_length{1000};
    const auto sequences_count{10};
    const auto test_runs{10};
    std::vector<Meas> meas;
    for(auto i{0}; i < test_runs; i++)
    {
        random_seq_generator rsg_standard_printer{sequence_length, sequences_count, std::make_unique<test_iostream_printer>()};
        rsg_standard_printer.generate_sequences();
        auto start = std::chrono::steady_clock::now();
        rsg_standard_printer.print_sequences();
        auto stop = std::chrono::steady_clock::now();
        auto standard_delta = stop - start;

        random_seq_generator rsg_lookup_printer{sequence_length, sequences_count, std::make_unique<test_lookup_printer>()};
        rsg_lookup_printer.generate_sequences();
        start = std::chrono::steady_clock::now();
        rsg_lookup_printer.print_sequences();
        stop = std::chrono::steady_clock::now();
        auto lookup_delta = stop - start;

        random_seq_generator rsg_ostream_printer{sequence_length, sequences_count, std::make_unique<test_ostream_printer>()};
        rsg_ostream_printer.generate_sequences();
        start = std::chrono::steady_clock::now();
        rsg_ostream_printer.print_sequences();
        stop = std::chrono::steady_clock::now();
        auto ostream_delta = stop - start;

        random_seq_generator rsg_fwrite_printer{sequence_length, sequences_count, std::make_unique<test_fwrite_printer>()};
        rsg_fwrite_printer.generate_sequences();
        start = std::chrono::steady_clock::now();
        rsg_fwrite_printer.print_sequences();
        stop = std::chrono::steady_clock::now();
        auto fwrite_delta = stop - start;

        random_seq_generator rsg_fwrite_lookup_printer{sequence_length, sequences_count, std::make_unique<test_fwrite_lookup_printer>()};
        rsg_fwrite_lookup_printer.generate_sequences();
        start = std::chrono::steady_clock::now();
        rsg_fwrite_lookup_printer.print_sequences();
        stop = std::chrono::steady_clock::now();
        auto fwrite_lookup_delta = stop - start;
        meas.push_back(Meas{
         std::chrono::duration_cast<std::chrono::nanoseconds> (standard_delta),
         std::chrono::duration_cast<std::chrono::nanoseconds> (lookup_delta),
         std::chrono::duration_cast<std::chrono::nanoseconds> (ostream_delta),
         std::chrono::duration_cast<std::chrono::nanoseconds> (fwrite_delta),
         std::chrono::duration_cast<std::chrono::nanoseconds> (fwrite_lookup_delta)});
    }
    std::cout<<"MEAS RESOULT\nstandard lookup ostream fwrite fwrite_lookup\n";
    for(auto m:meas)
    {
        std::cout<<m.standard.count()<<" "<<m.lookup.count()<<" "<<m.ostream.count()<<" "<<m.fwrite.count()<<" "<<m.fwrite_lookup.count()<<"\n";
    }
}