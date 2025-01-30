#pragma once
#include <cstddef>
#include <iostream>
#include <memory>
#include <random>
#include "printer.hpp"

class random_seq_generator
{
public:
    explicit random_seq_generator(std::size_t sequence_length, std::size_t count, std::unique_ptr<Iprinter> iprinter)
    : sequence_length{sequence_length}, count{count}, printer{std::move(iprinter)}
    {
        random_enginge = std::default_random_engine(device());
        uniform_dist = std::uniform_int_distribution<int>(0, printer->get_range());
    }
    void print_sequences()
    {
        for(auto j{0}; j<count; j++)
        {
            for(auto i{0}; i<sequence_length; i++)
            {
                printer->print(uniform_dist(random_enginge));
            }
            std::cout<<std::endl;
        }
    }
private:
    std::random_device device;
    std::default_random_engine random_enginge;
    std::uniform_int_distribution<int> uniform_dist;
    std::size_t sequence_length{0};
    std::size_t count{0};
    std::unique_ptr<Iprinter> printer;
};