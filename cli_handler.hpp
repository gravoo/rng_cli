#ifndef CLI_LIB_H
#define CLI_LIB_H
#include <cstddef>
#include <string>
#include <optional>

struct Config
{
    std::size_t length;
    std::size_t counnt;
    std::optional<std::string> alphabet;
};
Config get_config_from_cli(int argc, char **argv, std::string length_option, std::string count_option, std::string alphabet_option);

#endif //CLI_LIB