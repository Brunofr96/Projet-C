#ifndef GENERATOR_H
#define GENERATOR_H

#include "parser.h"

// Fonction pour générer un fichier Python basé sur les commandes
void generatePython(Command *commands, int commandCount, const char *outputFilename);

#endif
