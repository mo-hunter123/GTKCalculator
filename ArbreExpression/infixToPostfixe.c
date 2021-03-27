
#include "structures.c"


Cellule* Creer_cellule(char data){
    Cellule* NE = NULL; //déclaration du nouvel élément
 
    NE = (Cellule *)malloc(sizeof(Cellule)); //allocation dynamique pour la nouvelle Cellule
    if (!NE) //si le processus d’allocation ne passe pas bien
    {
        printf("\n il n’y a pas assez de mémoire pour créer cette cellule\n");
        exit(-1);
    }

    NE->val = data; //affectation de la valeur 
    NE->svt = NULL; //initialiser le suivant de notre cellule a null

    return ((Cellule *)NE); //retourner le nouvel élément  
}


int Existe_pile(Cellule *Pile){
    if(!Pile) //si la pile n’existe pas 
        return ((int)0); //on retourne faux

    return ((int)1);	//si oui on retourne vrai 
}


Cellule* Empiler_PPile(Cellule* Pile, char data){

    Cellule *NE = Creer_cellule(data); //Créer la cellule
    NE->svt = Pile; //insérer l'élément dans la pile
    return ((Cellule *)NE); //retourner la nouvelle tête
}


Cellule* Depiler_PPile(Cellule* Pile){
    Cellule *tmp; //L’adresse qu’on va libérer 

    if(!Existe_pile(Pile))
    { //Le cas ou la pile n’existe pas 
        printf("\nLa pile n'existe pas\n"); //on affiche un message
        return ((Cellule *)Pile);	//d’erreur
    }


    tmp = Pile; //stocker l'adresse 
    Pile = Pile->svt; //décalage du pointeur qui pointe sur la tête 				  de la pile 
    free(tmp); //libérer l'espace 
    return ((Cellule *)Pile); 
}


int priorite(char car)
{
    if((car == '-') || (car == '+'))
        return ((int)1);
    
    if((car == '/') || (car == '*'))
        return ((int)2);
}

void infixeToPostfixe(char *tab)
{
    Cellule *pile = NULL;
    char Remp[MaxElem];
    int i = 0, j =0;
    while (tab[i] != '\0')
    {
        switch (tab[i])
        {
        case ' ' : break;
        case '-':
        case '+':
        case '*':
        case '/':
            if(!Existe_pile(pile))
            {
                pile = Empiler_PPile(pile, tab[i]);
                Remp[j++] = ' ';
                break;
            }
            if(priorite(tab[i]) == priorite(pile->val))
            {
                Remp[j++] = ' ';
                Remp[j++] = pile->val;
                pile = Depiler_PPile(pile);
                pile = Empiler_PPile(pile,tab[i]);
                break;
            }
            if(priorite(tab[i]) > priorite(pile->val))
            {
                pile = Empiler_PPile(pile,tab[i]);
                Remp[j++] = ' ';
                break;
            }
            if(priorite(tab[i]) < priorite(pile->val))
            {
                Remp[j++] = ' ';
                while(Existe_pile(pile))
                {
                    Remp[j++] = pile->val;
                    pile = Depiler_PPile(pile);
                }
                pile = Empiler_PPile(pile,tab[i]);
                break;
            }
        default:
            Remp[j++] = tab[i];
            break;
        }
        i++;
    }
    Remp[j++] = ' ';
    while(Existe_pile(pile))
    {
        Remp[j++] = pile->val;
        pile = Depiler_PPile(pile);
    }
    Remp[j] = '\0';
    strcpy(tab, Remp);
    
}

