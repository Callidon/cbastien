/*
 * Fonctions de sérializations et de désérialization des piles de Pcode
 * Auteurs : Pierre Gaultier et Thomas Minier
 */
#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "structures.hpp"
#include "interpreter.hpp"
#include <fstream>
#include <string>

/*
 * Sérialize une pile de Pcode au format string et la stocke dans un fichier
 */
void serialize_stack(PcodeStack & stack, std::string filename);

/*
 * Désérialize une pile de Pcode contenue dans un fichier
 */
void deserialize_stack(PcodeStack & stack, std::string filename);

#endif
