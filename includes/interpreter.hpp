/*
 * Fonctions d'interprétations du Pseudo code
 * Auteurs : Pierre Gaultier et Thomas Minier
 */
#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <vector>
#include "pcode.hpp"

typedef std::vector<int> PcodeStack;
typedef std::vector<int> ExecStack;

/*
 * Méthode exécutant une série d'instructions en Pcode
 */
void execute(PcodeStack &pile_pcode, int nb_vars);

/*
 * Méthode interprétant la prochaine instruction en Pcode dans une pile
 * d'instructions
 */
void interprete(PcodeStack &pile_pcode, ExecStack &pile_x, int &co, int &spx);

#endif
