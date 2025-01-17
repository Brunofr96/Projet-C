#include "parser.h"   
#include "generator.h" 
#include <stdio.h>     
#include <stdlib.h>    

int main(int argc, char *argv[]) {
    // Vérification des arguments : le programme attend au moins un argument (nom du fichier d'entrée)
    if (argc < 2) {
        printf("Usage : %s <fichier_input.draw>\n", argv[0]); // Affiche le mode d'utilisation
        return 1; // Retourne une erreur si le fichier d'entrée n'est pas fourni
    }

    // Récupération du nom du fichier d'entrée
    const char *inputFilename = argv[1];
    int commandCount; // Variable pour stocker le nombre de commandes analysées
    // Appel de la fonction parseFile pour analyser le fichier d'entrée
    Command *commands = parseFile(inputFilename, &commandCount);

    // Vérification si l'analyse a échoué
    if (!commands) {
        printf("Erreur lors de l'analyse du fichier.\n"); // Affiche un message d'erreur
        return 1; // Retourne une erreur
    }

    // Appel de la fonction generatePython pour générer un fichier Python à partir des commandes
    generatePython(commands, commandCount, "output/dessin.py");

    // Message indiquant que le fichier Python a été généré
    printf("Fichier Python généré dans 'output/dessin.py'.\n");

    // Libération de la mémoire allouée dynamiquement pour chaque commande
    for (int i = 0; i < commandCount; i++) {
        free(commands[i].type); // Libération de la chaîne de caractères allouée pour le type de commande
    }
    free(commands); // Libération du tableau de commandes

    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}
