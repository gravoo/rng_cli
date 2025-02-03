#include "cli_handler.hpp"
#include "random_seq_generator.hpp"

int main(int argc, char** argv)
{
    std::string length_option{ "-l" };
    std::string count_option{ "-n" };
    std::string alphabet_option{ "-a" };
    auto config = get_config_from_cli(argc, argv, length_option, count_option, alphabet_option);

    random_seq_generator rsg{ config.length, config.counnt, printer_factory(config.alphabet) };
    rsg.generate_sequences();
    rsg.print_sequences();
}