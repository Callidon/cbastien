#include "scanner.hpp"
#include <iostream>
#include <stdlib.h>

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
	scanner->token->action = 0;
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
	string action = "";
	int code = -1;
	bool reading_action = false;
	while((! scanner->file->eof())) {
		current = scanner->file->get();
		if((current == ' ') || current == '\n') {
			scanner_consume_blanks(scanner);
			break;
		} else if(current == '\'') {
			// cas où c'est ELTER, on set le code et on saute la quote
			scanner->token->AType = Terminal;
			code = 17;
		} else if (current == '#') {
			// cas d'une action à ajouter au token
			scanner_consume_blanks(scanner);
			reading_action = true;
		} else if(reading_action) {
			action += current;
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
	if(action == "") {
		scanner->token->action = 0;
	} else {
		scanner->token->action = atoi(action.c_str());
	}
}

/*
 * Avance le scanner jusqu'au prochain token en passant les blancs et \n
 */
void scanner_consume_blanks(scanner_t * scanner) {
	char current;
	char next = scanner->file->peek();
	while((! scanner->file->eof())) {
		if((next != ' ') && next != '\n')
			break;
		current = scanner->file->get();
		next = scanner->file->peek();
	}
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
