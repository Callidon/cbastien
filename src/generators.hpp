#include "structures.hpp"

/*
 * Génère un noeud de type Atom
 */
Atom* GenAtom(int code, int action, ATOMTYPE type) {
	Atom * patom = new Atom;
	patom->code = code;
	patom->action = action;
	patom->AType = type;
	return patom;
}

/*
 * Génère un noeud de type Conc
 */
Conc* GenConc(Node* pa, Node* pb) {
	Conc * pconc = new Conc;
	pconc->left = pa;
	pconc->right = pb;
	return pconc;
}

// TODO faire la Memory Pool
