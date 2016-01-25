#include "generators.hpp"
#include "scanner.hpp"
#include <iostream>
using namespace std;

int main() {
	/*
	// Test de la forêt
	Go* go = GenForest();
	printForest(go);

	delete go;*/

	// Test du scanner
	Scanner * scanner = new Scanner;
	init_scanner("README.md", scanner);
	scan(scanner);
	cout << scanner->token << endl;
	scan(scanner);
	cout << scanner->token << endl;
	close_scanner(scanner);
	return 1;
}
