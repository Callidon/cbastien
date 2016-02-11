#ifndef TABLE_SYMBOLES_HPP
#define TABLE_SYMBOLES_HPP

#include <map>
#include <string>

typedef std::map<int, std::string> table_symboles_t;

void table_init_dicoT(table_symboles_t & table);

void table_init_dicoNT(table_symboles_t & table);

int table_get_code(table_symboles_t & table, std::string symbole);

#endif
