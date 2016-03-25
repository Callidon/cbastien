/*
 * Analyseurs des grammaires Go et GPL
 * Auteurs : Pierre Gaultier et Thomas Minier
 */
#ifndef ANALYSER_HPP
#define ANALYSER_HPP

#include <stack>
#include "actions.hpp"
#include "scanner.hpp"
#include "structures.hpp"
#include "table_symboles.hpp"

/*
 * Fonction analysant une grammaire pour vérifier si elle est correcte par
 * rapport à la GO
 */
bool analyse_go(Node *node, Go &go, std::stack<Node *> &pile,
                scanner_t *scanner, table_symboles_t &table);

/*
 * Fonction analysant une grammaire pour vérifier si elle est correcte par
 * rapport à la GPL
 */
bool analyse_gpl(Node *node, Go &go, std::stack<int> &pile,
                 table_symboles_t &table, scanner_gpl_t *scanner,
                 adresses_table_t &adresses, PcodeStack &pile_pcode);

#endif
