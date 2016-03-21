#include "generators.hpp"
#include <iostream>

using namespace std;

/*
 * Génère un noeud de type Conc
 */
Node *GenConc(Node *pleft, Node *pright) {
  Conc *pconc = new Conc;
  pconc->left = pleft;
  pconc->right = pright;
  pconc->classname = CONC;
  return pconc;
}

/*
 * Génère un noeud de type Union
 */
Node *GenUnion(Node *pleft, Node *pright) {
  Union *punion = new Union;
  punion->left = pleft;
  punion->right = pright;
  punion->classname = UNION;
  return punion;
}

/*
 * Génère un noeud de type Star
 */
Node *GenStar(Node *ptr) {
  Star *pstar = new Star;
  pstar->Star_e = ptr;
  pstar->classname = STAR;
  return pstar;
}

/*
 * Génère un noeud de type UN
 */
Node *GenUN(Node *ptr) {
  Un *pun = new Un;
  pun->Un_e = ptr;
  pun->classname = UN;
  return pun;
}

/*
 * Génère un noeud de type Atom
 */
Node *GenAtom(int code, int action, ATOMTYPE type) {
  Atom *patom = new Atom;
  patom->code = code;
  patom->action = action;
  patom->AType = type;
  patom->classname = ATOM;
  return patom;
}

/*
 * Génère le tableau contenant la grammaire des grammaires
 */
void GenForest(Go &go) {
  // règle S
  go[0] = GenConc(GenStar(GenConc(GenConc(GenConc(GenAtom(1, 0, NonTerminal),
                                                  GenAtom(6, 0, Terminal)),
                                          GenAtom(2, 0, NonTerminal)),
                                  GenAtom(9, 1, Terminal))),
                  GenAtom(5, 0, Terminal));
  // règle N
  go[1] = GenAtom(16, 2, Terminal);
  // règle E
  go[2] = GenConc(
      GenAtom(3, 0, NonTerminal),
      GenStar(GenConc(GenAtom(7, 0, Terminal), GenAtom(3, 3, NonTerminal))));
  // règle T
  go[3] = GenConc(
      GenAtom(4, 0, NonTerminal),
      GenStar(GenConc(GenAtom(8, 0, Terminal), GenAtom(4, 4, NonTerminal))));
  // règle F
  go[4] = GenUnion(
      GenUnion(
          GenUnion(GenUnion(GenAtom(16, 5, Terminal), GenAtom(17, 5, Terminal)),
                   GenConc(GenAtom(10, 0, Terminal),
                           GenConc(GenAtom(2, 0, NonTerminal),
                                   GenAtom(11, 0, Terminal)))),
          GenConc(GenAtom(12, 0, Terminal), GenConc(GenAtom(2, 0, NonTerminal),
                                                    GenAtom(13, 6, Terminal)))),
      GenConc(GenAtom(14, 0, Terminal),
              GenConc(GenAtom(2, 0, NonTerminal), GenAtom(15, 7, Terminal))));
}

/*
 * Affiche dans la sortie standard l'arbre à partir d'un noeud
 */
void printNode(Node *node, int prof, table_symboles_t &table_symboles) {
  int current_prof = prof + 1;

  for (int ind = 0; ind < current_prof; ind++) {
    cout << "---";
  }

  if (node->classname == CONC) {
    Conc *conc = static_cast<Conc *>(node);
    cout << "> Conc " << endl;
    printNode(conc->left, current_prof, table_symboles);
    printNode(conc->right, current_prof, table_symboles);
  } else if (node->classname == UNION) {
    Union *punion = static_cast<Union *>(node);
    cout << "> Union " << endl;
    printNode(punion->left, current_prof, table_symboles);
    printNode(punion->right, current_prof, table_symboles);
  } else if (node->classname == STAR) {
    Star *star = static_cast<Star *>(node);
    cout << "> Star " << endl;
    printNode(star->Star_e, current_prof, table_symboles);
  } else if (node->classname == UN) {
    Un *un = static_cast<Un *>(node);
    cout << "> UN " << endl;
    printNode(un->Un_e, current_prof, table_symboles);
  } else if (node->classname == ATOM) {
    Atom *atom = static_cast<Atom *>(node);
    cout << "> code : " << atom->code << " | char : '"
         << table_symboles[atom->code] << "' | action : " << atom->action
		 << " | type : " << atom->AType
         << endl;
  }
}

/*
 * Affiche dans la sortie les arbres de la grammaire des grammaires
 */
void printForest(Go &forest, table_symboles_t &table_symboles) {
  for (auto &it : forest) {
    cout << "Règle[" << it.first << "] " << table_symboles[it.first] << " : " << endl;
    printNode(it.second, 0, table_symboles);
  }
}
