#include "parser.h"
#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 

#define MAX_PARAMS 6 // Définition du nombre maximum de paramètres qu'une commande peut avoir

// Fonction qui analyse un fichier et retourne un tableau de structures "Command"
// filename : chemin du fichier à analyser
// commandCount : pointeur pour stocker le nombre total de commandes extraites
Command *parseFile(const char *filename, int *commandCount) {
    FILE *file = fopen(filename, "r"); // Ouverture du fichier en mode lecture
    if (!file) { // Vérification si le fichier n'a pas pu être ouvert
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        return NULL; // Retourne NULL en cas d'erreur
    }

    // Allocation dynamique d'un tableau de Command pour stocker jusqu'à 100 commandes
    Command *commands = malloc(100 * sizeof(Command)); 
    char line[256]; // Tableau pour lire une ligne du fichier
    *commandCount = 0; // Initialisation du compteur de commandes à 0

    // Lecture du fichier ligne par ligne
    while (fgets(line, sizeof(line), file)) {
        Command cmd; // Variable pour stocker une commande temporaire
        char type[10]; // Tableau pour stocker le type de commande
        // Utilisation de sscanf pour extraire le type de commande depuis la ligne
        int n = sscanf(line, "%s", type);

        if (n < 1) continue; // Si la ligne est vide ou mal formatée, elle est ignorée

        // Attribution du type de commande après duplication de la chaîne
        cmd.type = strdup(type);

        // Initialisation des paramètres de la commande à 0
        for (int i = 0; i < MAX_PARAMS; i++) {
            cmd.params[i] = 0;
        }

        // Extraction des paramètres restants à partir de la ligne
        int paramIndex = 0; // Index pour parcourir les paramètres
        char *token = strtok(line, " "); // Découpage de la ligne en tokens (le premier est le type)
        token = strtok(NULL, " "); // Passer au premier paramètre

        // Parcourir les tokens restants pour extraire les paramètres
        while (token != NULL && paramIndex < MAX_PARAMS) {
            cmd.params[paramIndex++] = atoi(token); // Conversion du token en entier et stockage
            token = strtok(NULL, " "); // Passer au token suivant
        }

        // Ajout de la commande au tableau des commandes et incrémentation du compteur
        commands[(*commandCount)++] = cmd;
    }

    fclose(file); // Fermeture du fichier après traitement
    return commands; // Retourne le tableau de commandes
}
