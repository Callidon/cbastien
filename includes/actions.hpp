/*
 * Actions utilisées lors des analyses des grammaires Go et GPL
 * Auteurs : Pierre Gaultier et Thomas Minier
 */
#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <map>
#include <stack>
#include "interpreter.hpp"
#include "structures.hpp"
#include "table_symboles.hpp"

typedef std::map<std::string, int> adresses_table_t;

/*
 * Fonction effectuant une action liée à la grammaire Go
 */
void go_action(table_symboles_t &table, Go &go, std::stack<Node *> &pile,
               std::string symbole, int atom_action, int symbole_action,
               ATOMTYPE catype);

/*
 * Fonction effectuant une action liée à la grammaire GPL
 */
void gpl_action(adresses_table_t &adresses, PcodeStack &pile_pcode,
                std::stack<int> &pile, std::string symbole, int action);

#endif
