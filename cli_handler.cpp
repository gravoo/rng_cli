#include <cstddef>
#include <iostream>
#include <argparse/argparse.hpp>
#include <optional>
#include "cli_handler.hpp"

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

std::optional<std::string> get_alphabet(std::optional<std::string> alphabet)
{
    if(alphabet)
    {
        return alphabet;
    }
    return std::optional<std::string>{};
}

Config get_config_from_cli(int argc, char **argv, std::string length_option, std::string count_option, std::string alphabet_option)
{
    argparse::ArgumentParser program("rng");
    program.add_argument(length_option)
        .help("length of generated sequences")
        .nargs(1, 1)
        .scan<'u', std::size_t>();

    program.add_argument(count_option)
        .help("count of generated sequences")
        .nargs(1, 1)
        .scan<'u', std::size_t>();

    program.add_argument(alphabet_option)
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
    auto sequence_length = get_sequence_length(program.present<std::size_t>(length_option));
    auto sequence_count = get_sequences_count(program.present<std::size_t>(count_option));
    auto alphabet = get_alphabet(program.present<std::string>(alphabet_option));
    return Config{sequence_length, sequence_count, alphabet};
}