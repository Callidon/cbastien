/*
 * Analyseurs des grammaires Go et GPL
 * Auteurs : Pierre Gaultier et Thomas Minier
 */
#include "analyser.hpp"
#include "actions.hpp"
using namespace std;

/*
 * Fonction analysant une grammaire pour vérifier si elle est correcte par
 * rapport à la GO
 */
bool analyse_go(Node* node, Go& go, stack<Node*>& pile, scanner_t* scanner,
                table_symboles_t& table) {
  bool correct = false;
  switch (node->classname) {
    // cas d'un noeud Conc
    case CONC: {
      Conc* conc = static_cast<Conc*>(node);
      if (analyse_go(conc->left, go, pile, scanner, table)) {
        correct = analyse_go(conc->right, go, pile, scanner, table);
      }
    } break;
    // cas d'un noeud Union
    case UNION: {
      Union* punion = static_cast<Union*>(node);
      if (analyse_go(punion->left, go, pile, scanner, table)) {
        correct = true;
      } else {
        correct = analyse_go(punion->right, go, pile, scanner, table);
      }
    } break;
    // cas d'un noeud Star
    case STAR: {
      Star* star = static_cast<Star*>(node);
      correct = true;
      while (analyse_go(star->Star_e, go, pile, scanner, table)) {
      }
    } break;
    // cas d'un noeud Un
    case UN: {
      Un* un = static_cast<Un*>(node);
      correct = true;
      analyse_go(un->Un_e, go, pile, scanner, table);
    } break;
    // cas d'un noeud Atom
    case ATOM: {
      Atom* atom = static_cast<Atom*>(node);
      switch (atom->AType) {
        case Terminal: {
          if (atom->code == scanner->token->code) {
            if (atom->action != 0) {
              go_action(table, go, pile, scanner->token->chaine, atom->action,
                        scanner->token->action, scanner->token->AType);
            }
            scan(scanner, table);
            correct = true;
          }
        } break;
        case NonTerminal: {
          if (analyse_go(go[atom->code], go, pile, scanner, table)) {
            if (atom->action != 0) {
              go_action(table, go, pile, scanner->token->chaine, atom->action,
                        scanner->token->action, scanner->token->AType);
            }
            correct = true;
          }
        } break;
      }
    } break;
  }
  return correct;
}

/*
 * Fonction analysant une grammaire pour vérifier si elle est correcte par
 * rapport à la GPL
 */
bool analyse_gpl(Node* node, Go& go, std::stack<int>& pile,
                 table_symboles_t& table, scanner_gpl_t* scanner,
                 adresses_table_t& adresses, PcodeStack& pile_pcode) {
  bool correct = false;
  switch (node->classname) {
    // cas d'un noeud Conc
    case CONC: {
      Conc* conc = static_cast<Conc*>(node);
      if (analyse_gpl(conc->right, go, pile, table, scanner, adresses,
                      pile_pcode)) {
        correct = analyse_gpl(conc->left, go, pile, table, scanner, adresses,
                              pile_pcode);
      }
    } break;
    // cas d'un noeud Union
    case UNION: {
      Union* punion = static_cast<Union*>(node);
      if (analyse_gpl(punion->right, go, pile, table, scanner, adresses,
                      pile_pcode)) {
        correct = true;
      } else {
        correct = analyse_gpl(punion->left, go, pile, table, scanner, adresses,
                              pile_pcode);
      }
    } break;
    // cas d'un noeud Star
    case STAR: {
      Star* star = static_cast<Star*>(node);
      correct = true;
      while (analyse_gpl(star->Star_e, go, pile, table, scanner, adresses,
                         pile_pcode)) {
      }
    } break;
    // cas d'un noeud Un
    case UN: {
      Un* un = static_cast<Un*>(node);
      correct = true;
      analyse_gpl(un->Un_e, go, pile, table, scanner, adresses, pile_pcode);
    } break;
    // cas d'un noeud Atom
    case ATOM: {
      Atom* atom = static_cast<Atom*>(node);
      switch (atom->AType) {
        case Terminal: {
          if (atom->code == scanner->token->code) {
            if (atom->action != 0) {
              gpl_action(adresses, pile_pcode, pile, scanner->token->chaine,
                         atom->action);
            }
            scan_gpl(scanner, table);
            correct = true;
          }
        } break;
        case NonTerminal: {
          if (analyse_gpl(go[atom->code], go, pile, table, scanner, adresses,
                          pile_pcode)) {
            if (atom->action != 0) {
              gpl_action(adresses, pile_pcode, pile, scanner->token->chaine,
                         atom->action);
            }
            correct = true;
          }
        } break;
      }
    } break;
  }
  return correct;
}
