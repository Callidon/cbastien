#ifndef ANALYSER_HPP
#define ANALYSER_HPP

#include <stack>
#include "structures.hpp"
#include "table_symboles.hpp"
#include "scanner.hpp"

/*
 * Fonction analysant une grammaire pour vérifier si elle est correcte par rapport à la GO
 */
bool analyse_go(Node * node, Go & go, std::stack<Node*> & pile, scanner_t * scanner, table_symboles_t & table);

/*
 * Fonction analysant une grammaire pour vérifier si elle est correcte par rapport à la GPL
 */
bool analyse_gpl(Node * node, Go & go, std::stack<Node*> & pile, scanner_gpl_t * scanner, table_symboles_t & table);

#endif
