/*
 * Fonctions de sérializations et de désérialization des piles de Pcode
 * Auteurs : Pierre Gaultier et Thomas Minier
 */
#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <fstream>
#include <string>
#include "interpreter.hpp"
#include "structures.hpp"

/*
 * Sérialize une pile de Pcode au format string et la stocke dans un fichier
 */
void serialize_stack(PcodeStack &stack, int nb_vars, std::string filename);

/*
 * Désérialize une pile de Pcode contenue dans un fichier
 */
void deserialize_stack(PcodeStack &stack, int &nb_vars, std::string filename);

#endif
