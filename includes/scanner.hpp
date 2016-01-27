#include <string>
#include <fstream>

#ifndef SCANNER_HPP
#define SCANNER_HPP

// Structure représentant un scanner de tokens
typedef struct {
	std::fstream * file;
	std::string token;
} Scanner;

/*
 * Initialise un scanner et ouvre le fichier dont le nom est passé en paramètre
 */
void init_scanner(std::string filename, Scanner * scanner);

/*
 * Ferme un scanner sur un fichier
 */
void close_scanner(Scanner * scanner);

/*
 * Fait avancer le scanner d'un token
 */
void scan(Scanner * scanner);

#endif
