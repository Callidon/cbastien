/*
 * Fonctions et strcutures liées à la table des symboles
 * Auteurs : Pierre Gaultier et Thomas Minier
 */
#include "table_symboles.hpp"
#include <iostream>

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
