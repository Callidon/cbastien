#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "pcode.hpp"
#include <vector>

typedef std::vector<int> PcodeStack;
typedef std::vector<int> ExecStack;

void execute(PcodeStack & pile_pcode);

void interprete(PcodeStack & pile_pcode, ExecStack & pile_x, unsigned int co, unsigned int spx);

#endif
