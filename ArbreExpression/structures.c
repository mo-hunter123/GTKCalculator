#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MaxElem 100


typedef struct ndd
{
    union Data {
        float operand;
        char operateur;
    } val;            //etiquette de noeud
    struct ndd *fg;   //pointeur sur le fils gauche
    struct ndd *fd;   //pointeur sur le fils droit
}Noeud;

typedef struct Pi{
    Noeud* nd;
    struct Pi *svt;
}Pile;

typedef struct cell{
    char val; //valeur de la cellule 
    struct cell *svt; //pointeur qui pointe sur l'élément suivant de la pile
}Cellule;