#include "analyser.hpp"
#include <iostream>
using namespace std;

/*
 * Fonction analysant une grammaire pour vérifier si elle est correcte
 */
bool analyse(Node * node, Go * go, scanner_t * scanner, table_symboles_t & table) {
	bool correct = false;
	switch(node->classname) {
		// cas d'un noeud Conc
		case CONC: {
			Conc * conc = static_cast<Conc*>(node);
			if(analyse(conc->left, go, scanner, table)) {
				correct = analyse(conc->right, go, scanner, table);
			}
		}
			break;
		// cas d'un noeud Union
		case UNION: {
			Union * punion = static_cast<Union*>(node);
			if(analyse(punion->left, go, scanner, table)) {
				correct = true;
			} else {
				correct = analyse(punion->right, go, scanner, table);
			}
		}
			break;
		// cas d'un noeud Star
		case STAR: {
			Star * star = static_cast<Star*>(node);
			correct = true;
			while(analyse(star->Star_e, go, scanner, table)) {}
		}
			break;
		// cas d'un noeud Un
		case UN: {
			Un * un = static_cast<Un*>(node);
			correct = true;
			analyse(un->Un_e, go, scanner, table);
		}
			break;
		// cas d'un noeud Atom
		case ATOM: {
			Atom * atom = static_cast<Atom*>(node);
			switch(atom->AType) {
				case Terminal: {
					if(atom->code == scanner->token->code) {
						if(atom->action != 0) {
							// do action
						}
						scan(scanner, table);
						correct = true;
					}
				}
					break;
				case NonTerminal: {
					if(analyse(go[atom->code], go, scanner, table)) {
						if(atom->action != 0) {
							// do action
						}
						correct = true;
					}
				}
					break;
			}
		}
			break;
	}
	return correct;
}
