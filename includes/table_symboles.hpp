#ifndef TABLE_SYMBOLES_HPP
#define TABLE_SYMBOLES_HPP

#include <map>
#include <string>
#include "structures.hpp"

// Type représentant une table de symbole
typedef std::map<int, std::string> table_symboles_t;

/*
 * Fonction initialisant une table de symboles
 */
void table_init(table_symboles_t & table);

/*
 * Fonction renvoyant le code associé à un symbole, et renvoyant -1 en cas de symbole non trouvé
 */
int table_get_code(table_symboles_t & table, std::string symbole);

/*
 * Fonction renvoyant le code associé à un symbole, et ajoutant le symbole s'il n'existe pas dans la table
 */
int table_search_code(table_symboles_t & table, std::string symbole);

/*
 * Fonction effectuant une action lié à la grammaire Go
 */
void go_action(table_symboles_t & table, Go & go, std::string symbole, int action, ATOMTYPE catype);

#endif
