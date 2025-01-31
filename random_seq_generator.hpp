#pragma once
#include <cstddef>
#include <memory>
#include <random>
#include <vector>
#include "printer.hpp"

class random_seq_generator
{
public:
    explicit random_seq_generator(std::size_t sequence_length, std::size_t count, std::unique_ptr<Iprinter> iprinter)
    : sequence_length{sequence_length}, count{count}, printer{std::move(iprinter)}
    {
        random_enginge = std::default_random_engine(device());
        uniform_dist = std::uniform_int_distribution<int>(0, printer->get_count_of_marks());
    }

    void generate_sequences()
    {
        std::vector<std::vector<int>> resoult;
        for(auto i{0}; i<count; i++)
        {
            resoult.push_back(generate_random_sequence());
        }
        sequences = resoult;
    }

    void print_sequences()
    {
        for(auto &sequence:sequences)
        {
           printer->print(sequence);
        }
    }
private:
    std::vector<int> generate_random_sequence()
    {
        std::vector<int> random_sequence;
        random_sequence.reserve(sequence_length);
        for(auto i{0}; i<sequence_length; i++)
        {
            random_sequence.push_back(uniform_dist(random_enginge));
        }
        return random_sequence;
    }
    std::random_device device;
    std::default_random_engine random_enginge;
    std::uniform_int_distribution<int> uniform_dist;
    std::size_t sequence_length{0};
    std::size_t count{0};
    std::unique_ptr<Iprinter> printer;
    std::vector<std::vector<int>> sequences;
};