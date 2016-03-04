#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "pcode.hpp"
#include <vector>

typedef std::vector<int> PcodeStack;
typedef std::vector<int> ExecStack;

/*
 * Méthode exécutant une série d'instructions Pcode
 */
void execute(PcodeStack & pile_pcode);

/*
 * Méthode interpérant la prochaine instruction Pcode dans une pile d'instructions
 */
void interprete(PcodeStack & pile_pcode, ExecStack & pile_x, int co, int spx);

#endif
