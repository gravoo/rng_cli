#pragma once

#include <stdint.h>
#include <string>
#include <vector>

char
simpleCheckSum(const std::string& data);

std::vector<uint16_t>
generateSequence(std::size_t length);
