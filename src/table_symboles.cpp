#include <stack>
#include "table_symboles.hpp"
#include "generators.hpp"

using namespace std;

const int NB_SYMBOLES = 18;

void table_init(table_symboles_t & table) {
	int i = 0;
	string symboles[NB_SYMBOLES] = {"S", "N", "E", "T", "F", ";", "->", "+", ".", ",", "(", ")", "[", "]", "(/", "/)","IDNTER", "ELTER"};
	for(i = 0; i < NB_SYMBOLES; i++) {
		table[i] = symboles[i];
	}
}

int table_get_code(table_symboles_t & table, string symbole) {
	int code = -1;
	for (map<int, string>::iterator it = table.begin(); it != table.end(); ++it) {
		if(it->second == symbole) {
			return it->first;
		}
	}
	// si le code n'a pas été trouvé, on retorune -1
	return code;
}

int table_search_code(table_symboles_t & table, string symbole) {
	int code;
	for (map<int, string>::iterator it = table.begin(); it != table.end(); ++it) {
		if(it->second == symbole) {
			return it->first;
		}
	}
	// si le code n'a pas été trouvé, on ajoute l'élément
	code = table.end()->first + 1;
	table[code] = symbole;
	return code;
}

void go_action(table_symboles_t & table, Go * go, string symbole, int action, ATOMTYPE catype) {
	Node * node_a, * node_b;
	stack<Node*> pile;
	switch(action) {
		case 1 : {
			node_a = pile.top();
			pile.pop();
			node_b = pile.top();
			pile.pop();
			Atom * atom = static_cast<Atom*>(node_b);
			go[atom->code + 5] = node_a;
		}
			break;
		case 2 : {
			pile.push(GenAtom(table_search_code(table, symbole), action, catype));
		}
			break;
		case 3 : {
			node_a = pile.top();
			pile.pop();
			node_b = pile.top();
			pile.pop();
			pile.push(GenUnion(node_a, node_b));
		}
			break;
		case 4 : {
			node_a = pile.top();
			pile.pop();
			node_b = pile.top();
			pile.pop();
			pile.push(GenConc(node_a, node_b));
		}
			break;
		case 5 : {
			if(catype == Terminal) {
				pile.push(GenAtom(table_search_code(table, symbole), action, Terminal));
			} else {
				pile.push(GenAtom(table_search_code(table, symbole), action, NonTerminal));
			}
		}
			break;
		case 6 : {
			node_a = pile.top();
			pile.pop();
			pile.push(GenStar(node_a));
		}
			break;
		case 7 : {
			node_a = pile.top();
			pile.pop();
			pile.push(GenUN(node_a));
		}
			break;
	}
}
