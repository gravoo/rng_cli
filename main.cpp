#include <cstddef>
#include <iostream>
#include <random>
#include "argh.h"

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
    auto cmdl = argh::parser({"-l ,-n, -a"});
    cmdl.parse(argc, argv);

    if (cmdl["-h"] || cmdl["--help"])
    {
        std::cout << "Usage:\n";
        std::cout << "-l=<length of generated sequence>\n";
        std::cout << "-n=<number of generated sequence>\n";
        std::cout << "-a=<alphabet> \n";
        return 0;
    }

    std::size_t sequence_length{8};
    cmdl("-l", sequence_length);
    if(!(cmdl({"-l"})>>sequence_length))
    {
        std::cerr << "Invalid sequence length, used default "<< sequence_length<< " instead \n";
    }

    std::size_t count{1};
    cmdl("-n", count);
    if(!(cmdl({"-n"})>>count))
    {
        std::cerr << "Invalid count of sequence, used default "<< count<< " instead \n";
    }

    random_seq_generator rsg(sequence_length, count);
    rsg.print_sequences();
}