#ifndef PARSER_H
#define PARSER_H
#include <time.h>  // Pour le temps
#include <unistd.h> // Pour sleep (Unix/Linux)

// Structure Commande qui contient le type de la commande et un tableau de paramètres (jusqu'à 4)
typedef struct Command {
    char *type;      // Type de commande : "advance", "square", "color", etc.
    int params[6];   // Tableau de paramètres : jusqu'à 6 paramètres
    int paramCount;
} Command;

// Fonction pour analyser une ligne de commande
int parseLine(char *line, Command *cmd);

// Fonction pour analyser un fichier .draw et retourner un tableau de commandes
Command *parseFile(const char *filename, int *commandCount);

#endif
