#include <stdio.h>
#include <string.h> // Ajout nécessaire pour strcmp
#include "generator.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Fonction pour ajuster les coordonnées en fonction de la taille de la fenêtre
void adjustCoordinates(int *x, int *y, int size, const char *shape) {
    // S'assurer que les formes ne dépassent pas la fenêtre (en prenant en compte la taille des formes)
    if (*x < -WINDOW_WIDTH / 2) *x = -WINDOW_WIDTH / 2;
    if (*x > WINDOW_WIDTH / 2) *x = WINDOW_WIDTH / 2;
    if (*y < -WINDOW_HEIGHT / 2) *y = -WINDOW_HEIGHT / 2;
    if (*y > WINDOW_HEIGHT / 2) *y = WINDOW_HEIGHT / 2;

    // Ajuster la taille du cercle ou du carré si nécessaire
    if (strcmp(shape, "circle") == 0 && size > WINDOW_WIDTH / 2) {
        size = WINDOW_WIDTH / 2;
    } else if (strcmp(shape, "square") == 0 && size > WINDOW_WIDTH / 2) {
        size = WINDOW_WIDTH / 2;
    }
}
void generatePython(Command *commands, int commandCount, const char *outputFilename) {
    FILE *file = fopen(outputFilename, "w");
    if (!file) {
        printf("Erreur : Impossible de créer le fichier %s\n", outputFilename);
        return;
    }

    // Variables pour compter les formes
    int squareCount = 0;
    int rectangleCount = 0;
    int circleCount = 0;
    // j'ajoute les autres compteurs pour chaque fonction

    fprintf(file, "import turtle\n\n");

    // Initialiser la fenêtre turtle avec la taille définie
    fprintf(file, "turtle.setup(%d, %d)\n\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    fprintf(file, "turtle.ht()\n");

    for (int i = 0; i < commandCount; i++) {
        Command cmd = commands[i];

        // Ignorer les lignes qui commencent par #
        if (cmd.type[0] == '#') {
            continue;
        }

        // Ajuster les paramètres pour ne pas dépasser la fenêtre
        int x = cmd.params[0], y = cmd.params[1], size = cmd.params[2];
        adjustCoordinates(&x, &y, size, cmd.type);

        if (strcmp(cmd.type, "circle") == 0) {
            // Déplacer la tortue à la position (x, y), puis dessiner le cercle
            fprintf(file, "turtle.penup()\n");
            fprintf(file, "turtle.goto(%d, %d)\n", x, y);
            fprintf(file, "turtle.pendown()\n");
            fprintf(file, "turtle.circle(%d)\n", size);
        } else if (strcmp(cmd.type, "line") == 0) {
            // Déplacer la tortue à la position (x1, y1), puis dessiner la ligne vers (x2, y2)
            int x2 = cmd.params[2], y2 = cmd.params[3];
            adjustCoordinates(&x2, &y2, 0, "line");
            fprintf(file, "turtle.penup()\n");
            fprintf(file, "turtle.goto(%d, %d)\n", x, y);
            fprintf(file, "turtle.pendown()\n");
            fprintf(file, "turtle.goto(%d, %d)\n", x2, y2);
        } else if (strcmp(cmd.type, "square") == 0) {
            // Déplacer la tortue à la position (x, y), puis dessiner le carré
            fprintf(file, "turtle.penup()\n");
            fprintf(file, "turtle.goto(%d, %d)\n", x, y);
            fprintf(file, "turtle.pendown()\n");
            for (int j = 0; j < 4; j++) {
                fprintf(file, "turtle.forward(%d)\n", size);
                fprintf(file, "turtle.right(90)\n");
            }
            squareCount++;

        } else if (strcmp(cmd.type, "color") == 0) {
            // Générer le code pour changer la couleur
            fprintf(file, "turtle.color(%d/255, %d/255, %d/255)\n", x, y, cmd.params[3]);
        } else if (strcmp(cmd.type, "advance") == 0) {
            // Commande advance : avance de la distance donnée
            if (x != 0) { // Assurer que x est initialisé avant de l'utiliser
                fprintf(file, "turtle.forward(%d)\n", x);
            }
        } else if (strcmp(cmd.type, "left") == 0) {
            // Commande left : tourne à gauche de l'angle donné
            if (x != 0) { // Assurer que x est initialisé avant de l'utiliser
                fprintf(file, "turtle.left(%d)\n", x);
            }
        } else if (strcmp(cmd.type, "right") == 0) {
            // Commande right : tourne à droite de l'angle donné
            if (x != 0) { // Assurer que x est initialisé avant de l'utiliser
                fprintf(file, "turtle.right(%d)\n", x);
            }
        } else if (strcmp(cmd.type, "orientTo") == 0) {
            // Commande orientTo : définir l'angle de la tortue
            if (x != 0) { // Assurer que x est initialisé avant de l'utiliser
                fprintf(file, "turtle.seth(%d)\n", x);
            }
        } else if (strcmp(cmd.type, "resetPosition") == 0) {
            // Commande reset : réinitialiser la tortue au centre
            fprintf(file, "turtle.penup()\n");
            fprintf(file, "turtle.setpos(0, 0)\n");
            fprintf(file, "turtle.pendown()\n");
        } else if (strcmp(cmd.type, "triangle")==0){
            int x2 = cmd.params[2], y2 = cmd.params[3], x3 = cmd.params[4], y3 = cmd.params[5];
            fprintf(file, "turtle.penup()\n");
            fprintf(file, "turtle.goto(%d, %d)\n", x, y);
            fprintf(file, "turtle.pendown()\n");
            fprintf(file, "turtle.goto(%d, %d)\n", x2, y2);
            fprintf(file, "turtle.pendown()\n");
            fprintf(file, "turtle.goto(%d, %d)\n", x3, y3);
            fprintf(file, "turtle.pendown()\n");
            fprintf(file, "turtle.goto(%d, %d)\n", x, y);
        } else if (strcmp(cmd.type, "rectangle") == 0) {

            // Id de la boite
            int num = cmd.params[0]; // Id de la boîte

            // Récupérer les paramètres (x, y, width, height)
            int width = cmd.params[2], height = cmd.params[3];


            // Ajuster les coordonnées du rectangle
            adjustCoordinates(&x, &y, 0, "rectangle");

            // Déplacer la tortue à la position de départ
            fprintf(file, "turtle.penup()\n");
            fprintf(file, "turtle.goto(%d, %d)\n", x, y);
            fprintf(file, "turtle.pendown()\n");

            // Dessiner le rectangle
            fprintf(file, "turtle.forward(%d)\n", width);       // Ligne supérieure
            fprintf(file, "turtle.right(90)\n");
            fprintf(file, "turtle.forward(%d)\n", height);      // Côté droit
            fprintf(file, "turtle.right(90)\n");
            fprintf(file, "turtle.forward(%d)\n", width);       // Ligne inférieure
            fprintf(file, "turtle.right(90)\n");
            fprintf(file, "turtle.forward(%d)\n", height);      // Côté gauche
            fprintf(file, "turtle.right(90)\n");

        
        } else if (strcmp(cmd.type, "deselect") == 0) {
            int num = cmd.params[0]; // Id de la boîte

            // Code pour effacer la boîte identifiée par num
            fprintf(file, "# Supprimer la boîte %d\n", num);
            fprintf(file, "turtle.clear()\n");



        } else {
            printf("Erreur : Commande '%s' inconnue\n", cmd.type);
        }
    }

     // Affichage du nombre de formes générées
    fprintf(file, "\n# Nombre de formes générées\n");
    fprintf(file, "print('Nombre de carrés:', %d)\n", squareCount);
    fprintf(file, "print('Nombre de rectangles:', %d)\n", rectangleCount);
    fprintf(file, "print('Nombre de cercles:', %d)\n", circleCount);

    fprintf(file, "\nturtle.done()\n");
    fclose(file);
}
