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
	scanner_gpl_t * scanner_gpl = new scanner_gpl_t;
	init_scanner("grammar.txt", scanner);
	init_scanner_gpl("main.txt", scanner_gpl);

	// Test de l'analyseur
	//on scan le premier token avant d'analyser
	scan(scanner, table);
	cout << "analyse de grammar.txt : " << analyse_go(go[0], go, pile, scanner, table) << endl;
	printForest(go, table);

	close_scanner(scanner);
	close_scanner_gpl(scanner_gpl);
	return 1;
}
