/*
 * Fonctions et strcutures liées à la table des symboles
 * Auteurs : Pierre Gaultier et Thomas Minier
 */
#ifndef TABLE_SYMBOLES_HPP
#define TABLE_SYMBOLES_HPP

#include "structures.hpp"
#include <map>
#include <stack>
#include <string>

// Type représentant une table de symbole
typedef std::map<int, std::string> table_symboles_t;

/*
 * Fonction initialisant une table de symboles
 */
void table_init(table_symboles_t &table);

/*
 * Fonction renvoyant le code associé à un symbole parmi ceux spécifiques à la
 * Go, et renvoyant -1 en cas de symbole non trouvé
 */
int table_go_get(table_symboles_t &table, std::string symbole);

/*
 * Fonction renvoyant le code associé à un symbole, et renvoyant -1 en cas de
 * symbole non trouvé
 */
int table_get(table_symboles_t &table, std::string symbole);

/*
 * Fonction renvoyant le code associé à un symbole, et ajoutant le symbole s'il
 * n'existe pas dans la table
 */
int table_search_code(table_symboles_t &table, std::string symbole);

#endif
