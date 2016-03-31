/*
 * Fonctions de sérializations et de désérialization des piles de Pcode
 * Auteurs : Pierre Gaultier et Thomas Minier
 */
#include "serializer.hpp"

using namespace std;

/*
 * Sérialize une pile de pcode au format string et la stocke dans un fichier
 */
void serialize_stack(PcodeStack& stack, int nb_vars, std::string filename) {
  fstream file(filename, fstream::out);
  // on ajoute le nombre de variables allouées en mémoire au début du fichier
  file << to_string(nb_vars);
  file << ' ';
  // on ajoute tous les éléments de la pile de pcode dans le fichier
  for (auto& it : stack) {
    file << to_string(it);
    file << ' ';
  }
}

/*
 * Désérialize une pile de pcode contenue dans un fichier
 */
void deserialize_stack(PcodeStack& stack, int& nb_vars, std::string filename) {
  fstream file(filename, fstream::in);
  string token;
  string current = "";
  bool find_nb_vars = false;
  while (!file.eof()) {
    current = file.get();
    while ((current != " ") && (current != "\n") && (!file.eof())) {
      token += current;
      current = file.get();
    }
    // si on a lu le nb de variable (le 1er chiffre du fichier)
    if (!find_nb_vars) {
      nb_vars = atoi(token.c_str());
      find_nb_vars = true;
      token = "";
    } else if (token != "") {
      stack.push_back(atoi(token.c_str()));
      token = "";
    }
  }
}
