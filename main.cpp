#include <cstddef>
#include <iostream>
#include <argparse/argparse.hpp>
#include <optional>
#include "random_seq_generator.hpp"

std::size_t get_sequence_length(std::optional<std::size_t> args_sequence)
{
    std::size_t default_sequence_length{8};
    if(args_sequence)
    {
        return *args_sequence;
    }
    return default_sequence_length;
}

std::size_t get_sequences_count(std::optional<std::size_t> args_sequences_count)
{
    std::size_t default_sequences_count{1};
    if(args_sequences_count)
    {
        return *args_sequences_count;
    }
    return default_sequences_count;
}

int main(int argc, char **argv)
{
    argparse::ArgumentParser program("rng");
    program.add_argument("-l")
        .help("length of generated sequences")
        .nargs(1, 1)
        .scan<'u', std::size_t>();

    program.add_argument("-n")
        .help("count of generated sequences")
        .nargs(1, 1)
        .scan<'u', std::size_t>();

    program.add_argument("-a")
        .nargs(1, 1)
        .help("set of characters for random sequences");

    program.add_description("Generate random number sequence");

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }


    random_seq_generator rsg{get_sequence_length(program.present<std::size_t>("-l")),
     get_sequences_count(program.present<std::size_t>("-n")),
     printer_factory(program.present("-a"))};
    rsg.print_sequences();
}