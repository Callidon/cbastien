#ifndef ANALYSER_HPP
#define ANALYSER_HPP

#include "structures.hpp"
#include "table_symboles.hpp"
#include "scanner.hpp"

bool analyse(Node * node, Go * go, bool correct, scanner_t * scanner, table_symboles_t & table);

#endif
