#include "generators.hpp"
#include "scanner.hpp"
#include <iostream>
using namespace std;

int main() {
	// init de la table des symboles
	table_symboles_t table;
	table_symboles_init(table);

	// Test de la forêt
	Go* go = GenForest();
	printForest(go, table);

	delete go;

	// Test du scanner
	/*Scanner * scanner = new Scanner;
	init_scanner("README.md", scanner);
	scan(scanner);
	cout << scanner->token << endl;
	scan(scanner);
	cout << scanner->token << endl;
	close_scanner(scanner);*/
	return 1;
}
