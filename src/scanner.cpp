#include "scanner.hpp"
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;

/*
 * Initialise un scanner et ouvre le fichier dont le nom est passé en paramètre
 */
void init_scanner(string filename, scanner_t *scanner) {
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
void close_scanner(scanner_t *scanner) {
  if (scanner->file->is_open()) {
    scanner->file->close();
  }
  delete scanner->token, scanner;
}

/*
 * Fait avancer le scanner d'un token
 */
void scan(scanner_t *scanner, table_symboles_t &table_symboles) {
  int code = -1;
  bool reading_action = false;
  char current;
  string token = "", action = "";

  while (!scanner->file->eof()) {
    current = scanner->file->get();
    if ((current == ' ') || (current == '\n')) {
      scanner_consume_blanks(scanner);
      break;
    } else if (current == '\'') {
      // cas où c'est ELTER, on set le code et on saute la quote
      scanner->token->AType = Terminal;
      code = 17;
    } else if (current == '#') {
      // cas d'une action à ajouter au token
      scanner_consume_blanks(scanner);
      reading_action = true;
    } else if (reading_action) {
      action += current;
    } else {
      token += current;
    }
  }
  // recherche du code correspondant au token dans la Go, s'il n'a pas déjà été
  // déterminé
  if (code == -1) {
    scanner->token->AType = NonTerminal;
    code = table_go_get(table_symboles, token);
    // si le code n'a toujours pas été trouvé, c'est un Non Terminal
    if (code == -1) {
      code = 16;
    }
  }
  scanner->token->chaine = token;
  scanner->token->code = code;
  if (action == "") {
    scanner->token->action = 0;
  } else {
    scanner->token->action = atoi(action.c_str());
  }
}

/*
 * Initialise un scanner de gpl et ouvre le fichier dont le nom est passé en
 * paramètre
 */
void init_scanner_gpl(string filename, scanner_gpl_t *scanner) {
  scanner->file = new fstream;
  scanner->file->open(filename, fstream::in);
  scanner->token = new token_gpl_t;
  scanner->token->value = "";
  scanner->token->type = NONE;
  scanner->idents = new vector<string>;
  scanner->identNext = false;
}

/*
 * Ferme un scanner de gpl sur un fichier
 */
void close_scanner_gpl(scanner_gpl_t *scanner) {
  if (scanner->file->is_open()) {
    scanner->file->close();
  }
  delete scanner->token, scanner->idents, scanner;
}

/*
 * Fait avancer le scanner de gpl d'un token
 */
void scan_gpl(scanner_gpl_t *scanner, table_symboles_t &table) {
  char current;
  string token = "";

  // on scanne tout le token
  while (!scanner->file->eof()) {
    current = scanner->file->get();
    if ((current == ' ') || (current == '\n')) {
      break;
    }
    token += current;
  }
  scanner->token->value = token;

  bool inIndentTable = find(scanner->idents->begin(), scanner->idents->end(),
                            token) != scanner->idents->end();

  // si le token est déjà dans la table des identificateurs
  if (inIndentTable) {
    scanner->token->type = IDENT;
    scanner->token->code = table_get(table, "ident");
  } else if (scanner->identNext) {
    // si le symbole a été indiqué comme un identificateur
    scanner->token->type = IDENT;
    scanner->token->code = table_get(table, "ident");
    // on met à jour le scanner
    scanner->idents->push_back(token);
    scanner->identNext = false;
} else if ((token == "var") || (token == "const") || (token == "Program")) {
    // si le token déclare un identificateur à venir
    scanner->token->type = SYMB;
    scanner->token->code = table_get(table, token);
    scanner->identNext = true;
  } else {
    // derniers cas : entier ou symbole
    int ascii_first = int(token[0]);
    if ((ascii_first >= 49) && (ascii_first <= 57)) {
      // cas d'un entier
      scanner->token->type = ENT;
      scanner->token->code = table_get(table, token);
    } else {
      // cas d'un symbole (==, <, <=, etc)
      scanner->token->type = SYMB;
      scanner->token->code = table_get(table, token);
    }
  }
}

/*
 * Avance le scanner jusqu'au prochain token en passant les blancs et \n
 */
void scanner_consume_blanks(scanner_t *scanner) {
  char current, next = scanner->file->peek();
  while (!scanner->file->eof()) {
    if ((next != ' ') && next != '\n') {
      break;
    }
    current = scanner->file->get();
    next = scanner->file->peek();
  }
}

/*
 * Imprime un token dans la sortie standard
 */
void print_token(token_t *token, table_symboles_t &table) {
  cout << "chaine : " << token->chaine << " | code : " << token->code
       << " | symbole : " << table[token->code] << " | AType : " << token->AType
       << " | action : " << token->action << endl;
}
