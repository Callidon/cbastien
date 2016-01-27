#include "scanner.hpp"

using namespace std;

/*
 * Initialise un scanner et ouvre le fichier dont le nom est passé en paramètre
 */
void init_scanner(string filename, Scanner * scanner) {
	fstream * file = new fstream;
	file->open(filename, fstream::in);
	scanner->file = file;
	scanner->token = "";
}

/*
 * Ferme un scanner sur un fichier
 */
void close_scanner(Scanner * scanner) {
	if(scanner->file->is_open()) {
		scanner->file->close();
	}
	delete scanner;
}

/*
 * Fait avancer le scanner d'un token
 */
void scan(Scanner * scanner) {
	char current;
	string token = "";
	while((! scanner->file->eof())) {
		current = scanner->file->get();
		if((current == ' ') || current == '\n')
			break;
		token += current;
	}
	scanner->token = token;
}
