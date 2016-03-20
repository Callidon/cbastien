#include "generators.hpp"
#include "scanner.hpp"
#include "analyser.hpp"
#include "serializer.hpp"
#include <iostream>
#include <string.h>
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
		if (strcmp(argv[1], "-h") == 0) {
			cout << "Compilateur extensible cbastien" << endl
				<< "Usage : ./cbastien <option> <arguments>" << endl
				<< "Arguments : " << endl
				<< "	-c <fichier-de-grammaire> <fichier-du-programme> : compile le programme passé en paramètre à l'aide de la grammaire précisée" << endl
				<< "	-x <fichier-de-pcode> : exécute le fichier de pcode passé en paramètre" << endl;
		} else if (strcmp(argv[1], "-c") == 0) {
			// on récupère le nom du fichier passé en paramètre
			string grammar_filename, prog_filename;
			if(argc != 4) {
				cerr << "Erreur : argument(s) manquant(s)" << endl << "Usage : ./cbastien -c <fichier-de-grammaire> <fichier-du-programme>" << endl;
				return 0;
			}
			grammar_filename.assign(argv[2]);
			prog_filename.assign(argv[3]);

			// init de la pile de symboles
			stack<Node*> pile;

			// init des scanners de la GO & de la GPL
			scanner_t * scanner = new scanner_t;
			scanner_gpl_t * scanner_gpl = new scanner_gpl_t;
			init_scanner(grammar_filename, scanner);
			init_scanner_gpl(prog_filename, scanner_gpl);

			// Test de l'analyseur
			//on scan le premier token avant d'analyser
			scan(scanner, table);
			cout << "analyse de grammar.txt : " << analyse_go(go[0], go, pile, scanner, table) << endl;
			printForest(go, table);

			close_scanner(scanner);
			close_scanner_gpl(scanner_gpl);

		} else if (strcmp(argv[1], "-x") == 0) {
			string pcode_filename;
			PcodeStack pcode;

			if(argc != 3) {
				cerr << "Erreur : argument manquant" << endl << "Usage : ./cbastien -x <fichier-de-pcode>" << endl;
				return 0;
			}

			pcode_filename.assign(argv[2]);
			// déserialization de la pile de pcode
			// deserialize_stack(pcode, pcode_filename);

			// exécution de la pile de pcode
			// execute(pcode);
		} else {
			cerr << "Erreur : option non reconnue" << endl << "Essayez ./cbastien -h pour afficher l'aide" << endl;
			return 0;
		}
	} else {
		cerr << "Erreur : arguments insuffisants" << endl << "Essayez ./cbastien -h pour afficher l'aide" << endl;
		return 0;
	}
	return 1;
}
