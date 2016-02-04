#include "analyse.hpp"

void analyse(Node * node, Go * go, Scanner * scanner) {
	bool correct = false;
	switch(node->classname) {
		case CONC: {
			Conc * conc = static_cast<Conc*>(node);
			if(analyse(conc->left, go, scanner)) {
				correct = analyse(conc->right, go, scanner);
			}
		}
			break;
		case UNION: {
			Union * punion = static_cast<Union*>(node);
			if(analyse(punion->left, go, scanner)) {
				correct = true;
			} else {
				correct = analyse(punion->right, go, scanner);
			}
		}
			break;
		case STAR: {
			Star * star = static_cast<Star*>(node);
			correct = analyse(star->Star_e, go, scanner);
		}
			break;
		case UN: {
			Un * un = static_cast<Un*>(node);
			correct = analyse(un->Un_e, go, scanner);
		}
			break;
		case ATOM: {
			Atom * atom = static_cast<Atom*>(node);
			switch(atom->AType) {
				case Terminal: {
					if(atom->code == scanner->code) {
						correct = true;
						if(atom->action != 0) {
							// do action
						}
						// do scan
					}
				}
					break;
				case NonTerminal: {
					if(analyse(go[atom->code], go, scanner)) {
						correct = true;
						if(atom->action != 0) {
							// do action
						}
					}
				}
					break;
			}
		}
			break;
	}
	return correct;
}
