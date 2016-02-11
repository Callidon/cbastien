#include "scanner.hpp"
#include <iostream>
using namespace std;

/*
 * Initialise un scanner et ouvre le fichier dont le nom est passé en paramètre
 */
void init_scanner(string filename, scanner_t * scanner) {
	scanner->file = new fstream;
	scanner->file->open(filename, fstream::in);
	scanner->token = new token_t;
	scanner->token->chaine = "";
	scanner->token->code = 0;
}

/*
 * Ferme un scanner sur un fichier
 */
void close_scanner(scanner_t * scanner) {
	if(scanner->file->is_open()) {
		scanner->file->close();
	}
	delete scanner->token;
	delete scanner;
}

/*
 * Fait avancer le scanner d'un token
 */
void scan(scanner_t * scanner, table_symboles_t & table_symboles) {
	char current;
	string token = "";
	int code = -1;
	// TODO add action
	while((! scanner->file->eof())) {
		current = scanner->file->get();
		if((current == ' ') || current == '\n') {
			break;
		} else if(current == '\'') {
			// cas où c'est ELTER, on set le code et on saute la quote
			scanner->token->AType = Terminal;
			code = 17;
		} else {
			token += current;
		}
	}
	// recherche du code correspondant au token, s'il n'a pas déjà été déterminé
	if(code == -1) {
		scanner->token->AType = NonTerminal;
		code = table_get_code(table_symboles, token);
		// si le code n'a pas été trouvé, c'est un Non Terminal
		if(code == -1) {
			code = 16;
		}
	}
	scanner->token->chaine = token;
	scanner->token->code = code;
}

/*
 * Imprime un token dans la sortie standard
 */
void print_token(token_t * token, table_symboles_t & table) {
	cout << "chaine : " << token->chaine
		<< " | code : " << token->code
		<< " | symbole : " << table[token->code]
		<< " | AType : " << token->AType
		<< " | action : " << token->action
		<< endl;
}
