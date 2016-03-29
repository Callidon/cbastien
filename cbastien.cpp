#include <string.h>
#include <iostream>
#include "analyser.hpp"
#include "generators.hpp"
#include "scanner.hpp"
#include "serializer.hpp"
using namespace std;

int main(int argc, char* argv[]) {
  // init de la table des symboles
  table_symboles_t table;
  table_init(table);

  // génération de la Go
  Go go;
  GenForest(go);

  // analyse des arguments passés au programme
  if (argc > 1) {
    if (strcmp(argv[1], "-h") == 0) {
      cout << "Compilateur extensible cbastien" << endl
           << "Usage : ./cbastien <option> <arguments>" << endl
           << "Arguments : " << endl
           << "	-c <fichier-de-grammaire> <fichier-du-programme> : "
              "compile le programme passé en paramètre à l'aide de la "
              "grammaire précisée"
           << endl
           << "	-x <fichier-de-pcode> : exécute le fichier de pcode "
              "passé en paramètre"
           << endl;
    } else if (strcmp(argv[1], "-c") == 0) {
      // on récupère le nom du fichier passé en paramètre
      string grammar_filename, prog_filename;
      if (argc != 4) {
        cerr << "Erreur : argument(s) manquant(s)" << endl
             << "Usage : ./cbastien -c <fichier-de-grammaire> "
                "<fichier-du-programme>"
             << endl;
        return 0;
      }
      grammar_filename.assign(argv[2]);
      prog_filename.assign(argv[3]);

      // init des différentes piles
      PcodeStack pile_pcode;
      adresses_table_t adresses;
      stack<Node*> pile_node;
      stack<int> pile_actions;

      // init des scanners de la GO & de la GPL
      scanner_t* scanner = new scanner_t;
      scanner_gpl_t* scanner_gpl = new scanner_gpl_t;
      init_scanner(grammar_filename, scanner);
      init_scanner_gpl(prog_filename, scanner_gpl);

      // Analyse de la GPL
      // on scan le premier token avant d'analyser
      scan(scanner, table);
      if (!analyse_go(go[0], go, pile_node, scanner, table)) {
        cerr << "Erreur : la grammaire " << grammar_filename
             << " fournie en argument est incorrecte" << endl;
        return 0;
      }

      // IMPORTANT : le premier symbole de la GPL est forcément à la case 18 de
      // go
      // Analyse du programme avec la GPL
      scan_gpl(scanner_gpl, table);
      if (!analyse_gpl(go[18], go, pile_actions, table, scanner_gpl, adresses,
                       pile_pcode)) {
        cerr << "Erreur : le programme " << prog_filename
             << " fourni en argument est incorrect" << endl;
        return 0;
      }

      serialize_stack(pile_pcode, adresses.size(), "examples/pcode.txt");

      // Affichage de la forêt
      cout << "Affichage de la forêt (Go) :" << endl;
      printForest(go, table);

      cout << "Le programme " << prog_filename << " a été compilé avec succès !"
           << endl;

      close_scanner(scanner);
      close_scanner_gpl(scanner_gpl);

    } else if (strcmp(argv[1], "-x") == 0) {
      string pcode_filename;
      PcodeStack pcode;
      int nb_vars = 0;

      if (argc != 3) {
        cerr << "Erreur : argument manquant" << endl
             << "Usage : ./cbastien -x <fichier-de-pcode>" << endl;
        return 0;
      }

      pcode_filename.assign(argv[2]);
      // déserialization de la pile de pcode
      deserialize_stack(pcode, nb_vars, pcode_filename);

      // exécution de la pile de pcode
      execute(pcode, nb_vars);
    } else {
      cerr << "Erreur : option non reconnue" << endl
           << "Essayez ./cbastien -h pour afficher l'aide" << endl;
      return 0;
    }
  } else {
    cerr << "Erreur : arguments insuffisants" << endl
         << "Essayez ./cbastien -h pour afficher l'aide" << endl;
    return 0;
  }
  return 1;
}
