#include "generators.hpp"
#include "scanner.hpp"
#include "analyser.hpp"
#include <iostream>
using namespace std;

int main() {
	// init de la table des symboles
	table_symboles_t table;
	table_init(table);

	// init de la pile de symboles
	stack<Node*> pile;

	// Test de la forêt
	Go go;
	GenForest(go);

	// Test du scanner
	scanner_t * scanner = new scanner_t;
	init_scanner("grammar.txt", scanner);

	// Test de l'analyseur
	//on scan le premier token avant d'analyser
	scan(scanner, table);
	cout << "analyse de grammar.txt : " << analyse(go[0], go, pile, scanner, table) << endl;
	//printForest(go, table);

	close_scanner(scanner);
	return 1;
}
