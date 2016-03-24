/*
 * Actions utilisées lors des analyses des grammaires Go et GPL
 * Auteurs : Pierre Gaultier et Thomas Minier
 */
#include "actions.hpp"
#include "generators.hpp"
using namespace std;

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
