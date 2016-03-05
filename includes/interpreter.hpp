#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "pcode.hpp"
#include <vector>

typedef std::vector<int> PcodeStack;
typedef std::vector<int> ExecStack;

/*
 * Méthode exécutant une série d'instructions en Pcode
 */
void execute(PcodeStack & pile_pcode);

/*
 * Méthode interprétant la prochaine instruction en Pcode dans une pile d'instructions
 */
void interprete(PcodeStack & pile_pcode, ExecStack & pile_x, int co, int spx);

#endif
