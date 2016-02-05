#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include "structures.hpp"
#include "table_symboles.hpp"

/*
 * Génère un noeud de type Conc
 */
Conc* GenConc(Node* pleft, Node* pright);

/*
 * Génère un noeud de type Union
 */
Union* GenUnion(Node* pleft, Node* pright);

/*
 * Génère un noeud de type Star
 */
Star * GenStar(Node* ptr);

/*
 * Génère un noeud de type UN
 */
Un * GenUN(Node* ptr);

/*
 * Génère un noeud de type Atom
 */
Atom* GenAtom(int code, int action, ATOMTYPE type);

/*
 * Génère le tableau contenant la grammaire des grammaires
 */
Go* GenForest();

/*
 * Affiche dans la sortie standard l'arbre à partir d'un noeud
 */
void printNode(Node* node, int prof, table_symboles_t & table_symboles);

/*
 * Affiche dans la sortie les arbres de la grammaire des grammaires
 */
void printForest(Go* forest, table_symboles_t & table_symboles);

#endif
