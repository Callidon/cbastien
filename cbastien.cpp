#include "generators.hpp"
#include "scanner.hpp"
#include "analyser.hpp"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	// init de la table des symboles
	table_symboles_t table;
	table_init(table);

	// génération de la Go
	Go go;
	GenForest(go);

	// analyse des arguments passés au programme
	if (argc > 1) {
		if (argv[1] == "-h") {
			// TODO prompt help
		} else {
			// on récupère le nom du fichier passé en paramètre
			string filename;
			if(argc == 3) {
				filename.assign(argv[2]);
			} else {
				cerr << "Erreur : le second paramètre doit être le nom du fichier à utiliser" << endl;
				return 0;
			}
			if (argv[1] == "-a") {
				// TODO do analyse_go
			} else if (argv[1] == "-c") {
				// TODO do analyse_gpl
			} else if (argv[1] == "-x") {
				// TODO do execution
			}
		}
	} else {
		// TODO prompt help
	}

	// init de la pile de symboles
	stack<Node*> pile;

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
