#include "table_symboles.hpp"
#include <iostream>
#include "generators.hpp"

using namespace std;

const int NB_SYMBOLES = 18;

/*
 * Fonction initialisant une table de symboles
 */
void table_init(table_symboles_t &table) {
  string symboles[NB_SYMBOLES] = {"S",  "N", "E",  "T",  "F",      ";",
                                  "->", "+", ".",  ",",  "(",      ")",
                                  "[",  "]", "(/", "/)", "IDNTER", "ELTER"};
  for (int i = 0; i < NB_SYMBOLES; i++) {
    table[i] = symboles[i];
  }
}

/*
 * Fonction renvoyant le code associé à un symbole parmi ceux spécifiques à la
 * Go, et renvoyant -1 en cas de symbole non trouvé
 */
int table_go_get(table_symboles_t &table, string symbole) {
  int code = -1, cpt = 0;
  for (auto &it : table) {
    // si on a dépassé les symbole de la Go, on renvoie -1
    if (cpt >= NB_SYMBOLES) {
      return -1;
    }
    if (it.second == symbole) {
      return it.first;
    }
    cpt++;
  }
  // si le code n'a pas été trouvé, on retorune -1
  return code;
}

/*
 * Fonction renvoyant le code associé à un symbole, et renvoyant -1 en cas de
 * symbole non trouvé
 */
int table_get(table_symboles_t &table, string symbole) {
  int code = -1;
  for (auto &it : table) {
    if (it.second == symbole) {
      return it.first;
    }
  }
  // si le code n'a pas été trouvé, on retorune -1
  return code;
}

/*
 * Fonction renvoyant le code associé à un symbole, et ajoutant le symbole s'il
 * n'existe pas dans la table
 */
int table_search_code(table_symboles_t &table, string symbole) {
  int code;
  for (auto &it : table) {
    if (it.second == symbole) {
      return it.first;
    }
  }
  // si le code n'a pas été trouvé, on ajoute l'élément
  code = table.end()->first;
  table[code] = symbole;
  return code;
}

/*
 * Fonction effectuant une action lié à la grammaire Go
 */
void go_action(table_symboles_t &table, Go &go, stack<Node *> &pile,
               string symbole, int atom_action, int symbole_action,
               ATOMTYPE catype) {
  Node *node_a, *node_b;
  switch (atom_action) {
    case 1: {
      node_a = pile.top();
      pile.pop();
      node_b = pile.top();
      pile.pop();
      Atom *atom = static_cast<Atom *>(node_b);
      go[atom->code] = node_a;
    } break;
    case 2: {
      pile.push(
          GenAtom(table_search_code(table, symbole), symbole_action, catype));
    } break;
    case 3: {
      node_a = pile.top();
      pile.pop();
      node_b = pile.top();
      pile.pop();
      pile.push(GenUnion(node_a, node_b));
    } break;
    case 4: {
      node_a = pile.top();
      pile.pop();
      node_b = pile.top();
      pile.pop();
      pile.push(GenConc(node_a, node_b));
    } break;
    case 5: {
      if (catype == Terminal) {
        pile.push(GenAtom(table_search_code(table, symbole), symbole_action,
                          Terminal));
      } else {
        pile.push(GenAtom(table_search_code(table, symbole), symbole_action,
                          NonTerminal));
      }
    } break;
    case 6: {
      node_a = pile.top();
      pile.pop();
      pile.push(GenStar(node_a));
    } break;
    case 7: {
      node_a = pile.top();
      pile.pop();
      pile.push(GenUN(node_a));
    } break;
  }
}

/*
 * Fonction effectuant une action lié à la grammaire GPL
 */
void gpl_action(table_symboles_t &table, Go &go, std::stack<Node *> &pile,
                std::string symbole, int atom_action, int symbole_action,
                ATOMTYPE catype) {}
