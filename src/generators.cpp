#include <iostream>
#include "generators.hpp"

using namespace std;

/*
 * Génère un noeud de type Conc
 */
Conc* GenConc(Node* pleft, Node* pright) {
	Conc * pconc = new Conc;
	pconc->left = pleft;
	pconc->right = pright;
	pconc->classname = CONC;
	return pconc;
}

/*
 * Génère un noeud de type Union
 */
Union* GenUnion(Node* pleft, Node* pright) {
	Union * punion = new Union;
	punion->left = pleft;
	punion->right = pright;
	punion->classname = UNION;
	return punion;
}

/*
 * Génère un noeud de type Star
 */
Star * GenStar(Node* ptr) {
	Star * pstar = new Star;
	pstar->Star_e = ptr;
	pstar->classname = STAR;
	return pstar;
}

/*
 * Génère un noeud de type UN
 */
Un * GenUN(Node* ptr) {
	Un * pun = new Un;
	pun->Un_e = ptr;
	pun->classname = UN;
	return pun;
}

/*
 * Génère un noeud de type Atom
 */
Atom* GenAtom(int code, int action, ATOMTYPE type) {
	Atom * patom = new Atom;
	patom->code = code;
	patom->action = action;
	patom->AType = type;
	patom->classname = ATOM;
	return patom;
}

/*
 * Génère le tableau contenant la grammaire des grammaires
 */
Go* GenForest() {
	// 0 = IDNTER, 1 = ELTER, 2 = (/, 3 = /)
	Go * go = new Go[5];
	// règle S TODO : mettre bon code ascii pour ->
	go[0] = GenConc(
				GenStar(
					GenConc(
						GenConc(
							GenConc(
								GenAtom(static_cast<int>('N'), 0, NonTerminal), GenAtom(62, 0, Terminal)
							),
							GenAtom(static_cast<int>('E'), 0 , NonTerminal)
						),
						GenAtom(static_cast<int>(','), 0, Terminal)
					)
				),
				GenAtom(static_cast<int>(';'), 0, Terminal)
			);
	// règle N TODO : mettre bon code ascii
	go[1] = GenAtom(0, 0, NonTerminal);
	// règle E
	go[2] = GenConc(GenAtom(static_cast<int>('T'), 0 , NonTerminal), GenStar(GenConc(GenAtom(static_cast<int>('+'), 0, Terminal), GenAtom(static_cast<int>('T'), 0, NonTerminal))));
	// règle T
	go[3] = GenConc(GenAtom(static_cast<int>('F'), 0 , NonTerminal), GenStar(GenConc(GenAtom(static_cast<int>('.'), 0, Terminal), GenAtom(static_cast<int>('F'), 0, NonTerminal))));
	// règle F TODO : mettre bon code ascii
	go[4] = GenUnion(
				GenUnion(
					GenUnion(
						GenUnion(
							GenAtom(0, 0, NonTerminal), GenAtom(1, 0, Terminal)
						),
							GenConc(
								GenAtom(static_cast<int>('('), 0, Terminal),
								GenConc(
									GenAtom(static_cast<int>('E'), 0, NonTerminal), GenAtom(static_cast<int>(')'), 0, Terminal)
								)
							)
						),
						GenConc(
							GenAtom(static_cast<int>('['), 0, Terminal),
							GenConc(
								GenAtom(static_cast<int>('E'), 0, NonTerminal), GenAtom(static_cast<int>(']'), 0, Terminal)
							)
						)
					),
					GenConc(
						GenAtom(static_cast<int>('{'), 0 , Terminal),
						GenConc(
							GenAtom(static_cast<int>('E'), 0, NonTerminal), GenAtom(static_cast<int>('}'), 0, Terminal)
						)
					)
				);
	return go;
}

/*
 * Affiche dans la sortie standard l'arbre à partir d'un noeud
 */
void printNode(Node* node, int prof, table_symboles_t & table_symboles) {
	int ind = 0;
	int current_prof = prof + 1;
	for(ind = 0; ind < current_prof; ind++) {
		cout << "---";
	}
	if(node->classname == CONC) {
		Conc * conc = static_cast<Conc*>(node);
		cout << ">conc " << endl;
		printNode(conc->left, current_prof, table_symboles);
		printNode(conc->right, current_prof, table_symboles);
	} else if(node->classname == UNION) {
		Union * punion = static_cast<Union*>(node);
		cout << ">union " << endl;
		printNode(punion->left, current_prof, table_symboles);
		printNode(punion->right, current_prof, table_symboles);
	} else if(node->classname == STAR) {
		Star * star = static_cast<Star*>(node);
		cout << ">star " << endl;
		printNode(star->Star_e, current_prof, table_symboles);
	} else if(node->classname == UN) {
		Un * un = static_cast<Un*>(node);
		cout << ">UN " << endl;
		printNode(un->Un_e, current_prof, table_symboles);
	} else if(node->classname == ATOM) {
		Atom * atom = static_cast<Atom*>(node);
		cout << "> " << table_symboles[atom->code] << endl; ;
	}
}

/*
 * Affiche dans la sortie les arbres de la grammaire des grammaires
 */
void printForest(Go* forest, table_symboles_t & table_symboles) {
	cout << "Règle S" << endl;
	printNode(forest[0], 0, table_symboles);
	cout << "Règle N" << endl;
	printNode(forest[1], 0, table_symboles);
	cout << "Règle E" << endl;
	printNode(forest[2], 0, table_symboles);
	cout << "Règle T" << endl;
	printNode(forest[3], 0, table_symboles);
	cout << "Règle F" << endl;
	printNode(forest[4], 0, table_symboles);
}
