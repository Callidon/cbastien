#include "structures.hpp"
#include "table_symboles.hpp"
#include <string>
#include <fstream>

#ifndef SCANNER_HPP
#define SCANNER_HPP

// Structure représentant un token
typedef struct {
	std::string chaine;
	int code;
	std::string action;
	ATOMTYPE AType;
} token_t;

// Structure représentant un scanner de tokens
typedef struct {
	std::fstream * file;
	token_t * token;
} scanner_t;

/*
 * Initialise un scanner et ouvre le fichier dont le nom est passé en paramètre
 */
void init_scanner(std::string filename, scanner_t * scanner);

/*
 * Ferme un scanner sur un fichier
 */
void close_scanner(scanner_t * scanner);

/*
 * Fait avancer le scanner d'un token
 */
void scan(scanner_t * scanner, table_symboles_t & table_symboles);

/*
 * Imprime un token dans la sortie standard
 */
void print_token(token_t * token, table_symboles_t & table);

#endif
