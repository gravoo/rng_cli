#ifndef SEQUENCE_GENERATION_H_
#define SEQUENCE_GENERATION_H_

#include <stdint.h>
#include <string>
#include <vector>

char
simpleCheckSum(const std::string& data);

std::vector<uint16_t>
generateSequence(std::size_t length, std::size_t range = 16);

std::string
translateResult(const std::string& alphabet,
                const std::vector<uint16_t>& input);

#endif // SEQUENCE_GENERATION_H_
