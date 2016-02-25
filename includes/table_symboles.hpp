#ifndef TABLE_SYMBOLES_HPP
#define TABLE_SYMBOLES_HPP

#include <map>
#include <string>
#include "structures.hpp"

typedef std::map<int, std::string> table_symboles_t;

void table_init(table_symboles_t & table);

int table_get_code(table_symboles_t & table, std::string symbole);

int table_search_code(table_symboles_t & table, std::string symbole);

void go_action(table_symboles_t & table, Go * go, std::string symbole, int action, ATOMTYPE catype);

#endif
