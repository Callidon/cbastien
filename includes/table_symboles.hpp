#ifndef TABLE_SYMBOLES_HPP
#define TABLE_SYMBOLES_HPP

#include <map>
#include <string>

typedef std::map<int, std::string> table_symboles_t;

void table_symboles_init(table_symboles_t & table);

int table_get_code(table_symboles_t & table, std::string symbole);

#endif