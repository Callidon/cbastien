/*
 * Actions utilisées lors des analyses des grammaires Go et GPL
 * Auteurs : Pierre Gaultier et Thomas Minier
 */
#include "actions.hpp"
#include <iostream>
#include "generators.hpp"
#include "pcode.hpp"
using namespace std;

/*
 * Fonction effectuant une action liée à la grammaire Go
 */
void go_action(table_symboles_t& table, Go& go, stack<Node*>& pile,
               string symbole, int atom_action, int symbole_action,
               ATOMTYPE catype) {
  Node *node_a, *node_b;
  switch (atom_action) {
    case 1: {
      node_a = pile.top();
      pile.pop();
      node_b = pile.top();
      pile.pop();
      Atom* atom = static_cast<Atom*>(node_b);
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
    default: {
      cerr << "Erreur : action GPL (" << atom_action << ") non supportée "
           << endl;
    } break;
  }
}

/*
 * Fonction effectuant une action liée à la grammaire GPL
 */
void gpl_action(adresses_table_t& adresses, PcodeStack& pile_pcode,
                std::stack<int>& pile, string symbole, int action) {
  switch (action) {
    // réservation de mémoire pour une variable
    case 1: {
      if (adresses.size() == 0) {
        adresses[symbole] = 0;
      } else {
        // on affecte à la prochaine adresse disponible
        int adr = adresses.size();
        adresses[symbole] = adr;
      }
    } break;
    // chagrement de l'adresse d'une variable
    case 2: {
      pile_pcode.push_back(LDA);
      pile_pcode.push_back(adresses[symbole]);
    } break;
    // chargement de la valeur d'une variable
    case 3: {
      pile_pcode.push_back(LDV);
      pile_pcode.push_back(adresses[symbole]);
    } break;
    // chargement d'une constante
    case 4: {
      pile_pcode.push_back(LDC);
      pile_pcode.push_back(atoi(symbole.c_str()));
    } break;
    // affectation
    case 5: {
      pile_pcode.push_back(AFF);
    } break;
    // emplier l'opérateur +
    case 6: {
      pile.push(ADD);
    } break;
    // emplier l'opérateur -
    case 7: {
      pile.push(MOINS);
    } break;
    // emplier l'opérateur *
    case 8: {
      pile.push(MULT);
    } break;
    // emplier l'opérateur /
    case 9: {
      pile.push(DIV);
    } break;
    // chargement de la valeur d'une variable et dépiler un opérateur
    case 10: {
      pile_pcode.push_back(LDV);
      pile_pcode.push_back(adresses[symbole]);
      pile_pcode.push_back(pile.top());
      pile.pop();
    } break;
    // chargement de la valeur d'une constante et dépiler un opérateur
    case 11: {
      pile_pcode.push_back(LDC);
      pile_pcode.push_back(atoi(symbole.c_str()));
      pile_pcode.push_back(pile.top());
      pile.pop();
    } break;
    // empiler l'opérateur Write
    case 12: {
      pile.push(WRT);
    } break;
    // empiler l'opérateur Writeln
    case 13: {
      pile.push(WRTLN);
    } break;
    // instruction STOP
    case 14: {
      pile_pcode.push_back(STOP);
    } break;
    default: {
      cerr << "Erreur : action GPL (" << action << ") non supportée " << endl;
    } break;
  }
}
