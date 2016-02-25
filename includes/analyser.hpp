#ifndef ANALYSER_HPP
#define ANALYSER_HPP

#include "structures.hpp"
#include "table_symboles.hpp"
#include "scanner.hpp"

/*
 * Fonction analysant une grammaire pour vérifier si elle est correcte
 */
bool analyse(Node * node, Go & go, scanner_t * scanner, table_symboles_t & table);

#endif
