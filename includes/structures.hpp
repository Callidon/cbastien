#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <map>

// Type d'une feuille
enum ATOMTYPE {
	Terminal,
	NonTerminal
};

// Type d'une opération/noeud
enum Operation {
	CONC,
	UNION,
	STAR,
	UN,
	ATOM
};

// Noeud d'un arbre
typedef struct _Node {
	Operation classname;
} Node;

// Noeud représentant une concaténation
typedef struct _Conc : public Node {
	Node * left;
	Node * right;
	~_Conc() { delete left, right; }
} Conc;

// Noeud représentant une union
typedef struct _Union : public Node {
	Node * left;
	Node * right;
	~_Union() { delete left, right; }
} Union;

// Noeud représentant une opération [x]
typedef struct _Star : public Node {
	Node * Star_e;
	~_Star() { delete Star_e; }
} Star;

// Noeud représentant une opération (/x/)
typedef struct _Un : public Node {
	Node * Un_e;
	~_Un() { delete Un_e; }
} Un;

// Noeud représentant un terminal ou non-terminal
typedef struct _Atom : public Node {
	int code;
	int action;
	ATOMTYPE AType;
	~_Atom() { }
} Atom;

// Tableau de la grammaire des grammaires
typedef std::map<int, Node*> Go;

#endif
