#include "structures.hpp"
#include "table_symboles.hpp"
#include <fstream>
#include <vector>
#include <string>

#ifndef SCANNER_HPP
#define SCANNER_HPP

// Type d'un token reconnu par le scanner_gpl
enum TokenGPLType { ENT = 1, IDENT = 2, SYMB = 3, NONE = 4 };

// Structure représentant un token
typedef struct {
  std::string chaine;
  int code;
  int action;
  ATOMTYPE AType;
} token_t;

// Structure représentant un token utilisable par la GPL
typedef struct {
  TokenGPLType type;
  std::string value;
  int code;
} token_gpl_t;

// Structure représentant un scanner de tokens
typedef struct {
  std::fstream *file;
  token_t *token;
} scanner_t;

// Structure représentant un scanner de tokens utilisables par la GPL
typedef struct {
  std::fstream *file;
  token_gpl_t *token;
  std::vector<std::string> *idents;
  bool identNext;
} scanner_gpl_t;

/*
 * Initialise un scanner et ouvre le fichier dont le nom est passé en paramètre
 */
void init_scanner(std::string filename, scanner_t *scanner);

/*
 * Ferme un scanner sur un fichier
 */
void close_scanner(scanner_t *scanner);

/*
 * Fait avancer le scanner d'un token
 */
void scan(scanner_t *scanner, table_symboles_t &table_symboles);

/*
 * Initialise un scanner de gpl et ouvre le fichier dont le nom est passé en
 * paramètre
 */
void init_scanner_gpl(std::string filename, scanner_gpl_t *scanner);

/*
 * Ferme un scanner de gpl sur un fichier
 */
void close_scanner_gpl(scanner_gpl_t *scanner);

/*
 * Fait avancer le scanner de gpl d'un token
 */
void scan_gpl(scanner_gpl_t *scanner, table_symboles_t & table);

/*
 * Avance le scanner jusqu'au prochain token en passant les blancs et \n
 */
void scanner_consume_blanks(scanner_t *scanner);

/*
 * Imprime un token dans la sortie standard
 */
void print_token(token_t *token, table_symboles_t &table);

#endif
