/*
 * Actions utilisées lors des analyses des grammaires Go et GPL
 * Auteurs : Pierre Gaultier et Thomas Minier
 */
#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include "structures.hpp"
#include "table_symboles.hpp"
#include <map>
#include <stack>

typedef std::map<std::string, int> adresses_table_t;

/*
 * Fonction effectuant une action lié à la grammaire Go
 */
void go_action(table_symboles_t &table, Go &go, std::stack<Node *> &pile,
               std::string symbole, int atom_action, int symbole_action,
               ATOMTYPE catype);

/*
 * Fonction effectuant une action lié à la grammaire GPL
 */
void gpl_action(table_symboles_t &table, Go &go, std::stack<Node *> &pile,
			    std::string symbole, int atom_action, int symbole_action,
			    ATOMTYPE catype);

#endif
