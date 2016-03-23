#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "structures.hpp"
#include "interpreter.hpp"
#include <fstream>
#include <string>

void serialize_stack(PcodeStack & stack, std::string filename);

void deserialize_stack(PcodeStack & stack, std::string filename);

#endif
