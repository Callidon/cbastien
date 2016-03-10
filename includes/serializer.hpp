#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "structures.hpp"
#include "interpreter.hpp"
#include <fstream>
#include <string>

void serialize_forest(Go & go, std::string filename);

void serialize_node(Node * node, std::fstream * file);

void deserialize_forest(Go & go, std::string filename);

Node * deserializer_node(std::string token);

void serialize_stack(PcodeStack & stack, std::string filename);

void deserialize_stack(PcodeStack & stack, std::string filename);

#endif
