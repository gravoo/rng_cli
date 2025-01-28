#include <cstddef>
#include <iostream>
#include <random>
#include <argparse/argparse.hpp>

class random_seq_generator
{
public:
    explicit random_seq_generator(std::size_t number_length, std::size_t count) : sequence_length(number_length), count(count)
    {
        random_enginge = std::default_random_engine(device());
        uniform_dist = std::uniform_int_distribution<int>(0, 15);
    }
    void print_sequences()
    {
        for(auto j{0}; j<count; j++)
        {
            for(auto i{0}; i<sequence_length; i++)
            {
                std::cout<<std::hex<<uniform_dist(random_enginge);
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
};

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

    auto sequence_length = program.get<std::size_t>("-l");
    auto sequences_count = program.get<std::size_t>("-n");
    random_seq_generator rsg(sequence_length, sequences_count);
    rsg.print_sequences();
}