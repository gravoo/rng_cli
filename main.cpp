#include <memory>
#include <cstddef>
#include <iostream>
#include <argparse/argparse.hpp>
#include "random_seq_generator.hpp"

int main(int argc, char **argv)
{
    argparse::ArgumentParser program("rng");
    program.add_argument("-l","--l")
        .help("length of generated sequences")
        .default_value(std::size_t{8})
        .scan<'u', std::size_t>();

    program.add_argument("-n","--n")
        .help("count of generated sequences")
        .default_value(std::size_t{1})
        .scan<'u', std::size_t>();

    program.add_argument("-a","--a")
        .help("alphabet");

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

    auto default_hex_range{15};
    std::unique_ptr<Iprinter> printer = std::make_unique<hex_printer>(default_hex_range);

    if(auto alphabet = program.present("-a"))
    {
        printer = std::make_unique<alphabet_printer>(*alphabet);
    }

    auto sequence_length = program.get<std::size_t>("-l");
    auto sequences_count = program.get<std::size_t>("-n");
    random_seq_generator rsg(sequence_length, sequences_count, std::move(printer));
    rsg.print_sequences();
}