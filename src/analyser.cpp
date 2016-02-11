#include "analyser.hpp"
#include <iostream>
using namespace std;

bool analyse(Node * node, Go * go, bool correct, scanner_t * scanner, table_symboles_t & table) {
	switch(node->classname) {
		// cas d'un noeud Conc
		case CONC: {
			Conc * conc = static_cast<Conc*>(node);
			if(analyse(conc->left, go, correct, scanner, table)) {
				correct = analyse(conc->right, go, correct, scanner, table);
			} else {
				correct = false;
			}
		}
			break;
		// cas d'un noeud Union
		case UNION: {
			Union * punion = static_cast<Union*>(node);
			if(analyse(punion->left, go, correct, scanner, table)) {
				correct = true;
			} else {
				correct = analyse(punion->right, go, correct, scanner, table);
			}
		}
			break;
		// cas d'un noeud Star
		case STAR: {
			Star * star = static_cast<Star*>(node);
			correct = true;
			while(correct = analyse(star->Star_e, go, correct, scanner, table)) {}
		}
			break;
		// cas d'un noeud Un
		case UN: {
			Un * un = static_cast<Un*>(node);
			correct = true;
			correct = analyse(un->Un_e, go, correct, scanner, table);
		}
			break;
		// cas d'un noeud Atom
		case ATOM: {
			Atom * atom = static_cast<Atom*>(node);
			switch(atom->AType) {
				case Terminal: {
					cout << "salut, terminal in da place " << table[atom->code] << endl;
					cout << "atom code " << atom->code << ", token code " << scanner->token->code << endl;
					if(atom->code == scanner->token->code) {
						if(atom->action != 0) {
							// do action
						}
						scan(scanner, table);
						correct = true;
					} else {
						correct = false;
					}
				}
					break;
				case NonTerminal: {
					if(analyse(go[atom->code], go, correct, scanner, table)) {
						if(atom->action != 0) {
							// do action
						}
						correct = true;
					} else {
						correct = false;
					}
				}
					break;
			}
		}
			break;
	}
}
