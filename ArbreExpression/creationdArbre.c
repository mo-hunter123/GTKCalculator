
#include "infixToPostfixe.c"

//fonction pour convertir une chaine de caractere vers un reel 
float partie_fractionnaire(char tab[MaxElem], int *indice, float res){
    float dix=0.1; //declaration
    float reel;    //des variables
    reel = res;
    
    //tant que le caractere passe n'est pas un espace
    while(tab[*indice] != ' ')
    { 
        switch (tab[*indice])
        { 	 
            //gestion des cas possible
            case '0': reel = reel;break;
            case '1': reel = reel + (1.0 * dix);break; //ou ‘1’
            case '2': reel = reel + (2.0 * dix);break; //ou ‘2’
            case '3': reel = reel + (3.0 * dix);break; //ou ‘3’
            case '4': reel = reel + (4.0 * dix);break; //ou ‘4’
            case '5': reel = reel + (5.0 * dix);break; //ou ‘5’
            case '6': reel = reel + (6.0 * dix);break; //ou ‘6’
            case '7': reel = reel + (7.0 * dix);break; //ou ‘7’
            case '8': reel = reel + (8.0 * dix);break; //ou ‘8’
            case '9': reel = reel + (9.0 * dix);break; //ou ‘9’
            //si on trouve un autre point dans l'expression
            case'.': 
                printf("\nErreur de la saisie\n");
                exit(-1);
            default:
                printf("\nErreur de la saisie\n");
                exit(-1);
        }
        (*indice)++;
        dix = dix/10.;
    }
    return ((float)reel);
} //fin du programme


//fonction pour calculer la partie naturel
float partie_naturel(char tab[MaxElem], int *indice)
{
    float res = 0; // initialisation de resultat
    while(tab[*indice] != ' ')
    {
        switch (tab[*indice]) //manager les cas possible
        { 
            case '.': (*indice)++;  
                        return((float)partie_fractionnaire(tab,indice,res));
            case '0': res = res * 10;break; // ‘0’ 
            case '1': res = (res * 10) + 1;break; // ‘1’
            case '2': res = (res * 10) + 2;break; // ‘2’
            case '3': res = (res * 10) + 3;break; // ‘3’
            case '4': res = (res * 10) + 4;break; // ‘4’
            case '5': res = (res * 10) + 5;break; // ‘5’
            case '6': res = (res * 10) + 6;break; // ‘6’
            case '7': res = (res * 10) + 7;break; // ‘7’
            case '8': res = (res * 10) + 8;break; // ‘8’
            case '9': res = (res * 10) + 9;break; // ‘9’

            //si la valeur passe pas un nombre
            default:    
                printf("\nErreur de la saisie\n");
                exit(-1);
        }
        (*indice)++; 
    } //fin de while(tab[*indice] != ' ')
}//fin de la fonctionne 



int EstOperateur(char c){
    if(c == '+' || c == '-' || c == '/' || c == '*')
        return ((int)1);

    return ((int)0);
}

int Arb_est_vide(Noeud* Arb)
{
    if(!Arb)
        return ((int)1);    //arbre est vide
   
    return ((int)0);        //arbre n'est pas vide 
}

//creer le noeud de la pile pour l'operande
Pile* Creer_Noeud_Operand_Pile(float val){
    Pile *NE; //le nouveau element a inserer 
    NE = (Pile*)malloc(sizeof(Pile)); // resever l'espace pour le noeud de la pile 
    NE->nd = (Noeud*)malloc(sizeof(Noeud)); // reservation pour le noeud de l'arbre 
    NE->nd->val.operand = val; //affectation de la valeur (operande) 
    NE->nd->fg = NULL; // initialisation
    NE->nd->fd = NULL; //des differents
    NE->svt = NULL; // champs
    return ((Pile*)NE); //Noeud resultat
}

//creer le noeud de la pile pour l'operateur
Pile* Creer_Noeud_Operateur_Pile(char val){
    Pile *NE;//le nouveau element a inserer 
    NE = (Pile*)malloc(sizeof(Pile));// resever l'espace pour le noeud de la pile 
    NE->nd = (Noeud*)malloc(sizeof(Noeud));// reservation pour le noeud de l'arbre 
    NE->nd->val.operateur = val; //affectation de la valeur (operateur)
    NE->nd->fg = NULL; // initialisation
    NE->nd->fd = NULL; //des differents
    NE->svt = NULL; // champs
    return ((Pile*)NE); //Noeud resultat
}

/*la pile d'aide pour remplir l'arbre */
//Empiler dans la pile 
Pile *Empiler(Pile *PPile, Pile* Cell){

    if(!PPile)//si la pile est vide 
        return ((Pile*)Cell);
    
    Cell->svt = PPile; //Empiler la cellule 
    return ((Pile*)Cell); //retourner la tete de la pile
}


//Depiler dans la pile 
Pile *Depiler(Pile* PPile){
    //si la pile est vide 
    if(!PPile){
        printf("\npile vide\n");
        return ((Pile*)PPile);
    }

    Pile *tmp; //aide d'un temporaire 
    tmp = PPile;
    PPile = PPile->svt; //depiler la tete 
    free(tmp); //liberer l'espace 
    return ((Pile*)PPile);   
}


//Fonction de creation de l'arbre 
Noeud* creerArbreExpression(char expPostfixe[MaxElem]){

    Pile *PPile; //pile d'aide 
    Pile *cellOperateur = NULL; //cellule qui va contenir l'operateur 
    Noeud *cellOperand1; //cellule de la premiere tete
    Noeud *cellOperand2; //cellule de la deuxieme tete
    int indice; //indice pour parcourir l'expression 
    float res; //le reel a empiler 
    for (indice = 0; indice < strlen(expPostfixe); indice++)
    {
        
        //si l'element est un operand on empile
        if(!EstOperateur(expPostfixe[indice]))
        {   
            //convertir le resultat 
            res = partie_naturel(expPostfixe,&indice);
            //le noeud d'operande 
            cellOperateur = Creer_Noeud_Operand_Pile(res);
            //empiler l'operande 
            PPile = Empiler(PPile, cellOperateur);
        }
            
        else //si c'est un operateur
        {
            cellOperateur = Creer_Noeud_Operateur_Pile(expPostfixe[indice]);

            //depiler deux cellule
            cellOperand1 = PPile->nd;//prendre la tete
            PPile = Depiler(PPile);//supprimer la tete

            cellOperand2 = PPile->nd;
            PPile = Depiler(PPile);

            //les deux tetes seront les fils d'operateur 
            cellOperateur->nd->fd = cellOperand1;
            cellOperateur->nd->fg = cellOperand2;

            //et on ajoute toute l'arbre
            PPile = Empiler(PPile, cellOperateur);
        }
        
    }
    //l'arbre resultante 
    return ((Noeud*)(cellOperateur->nd));       
}
