
#include "creationdArbre.c"


void affichage_infixe_expresseion(Noeud *racine)
{
    if(!Arb_est_vide(racine))
    {
        affichage_infixe_expresseion(racine->fg);
        if( (!racine->fd) && (!racine->fd) )
            printf("%g ", racine->val.operand);
        else printf("%c ", racine->val.operateur);
        affichage_infixe_expresseion(racine->fd);        
    }
}

float calculer(float a, float b, char op)
{
    switch (op)
    {
        case '+':
            return((float)a+b);
            break;

        case '*':
            return((float)a*b);
            break;

        case '-':
            return((float)a-b);
            break;

        case '/':
            if(b != 0)return((float)a/b);
            else 
            {
                printf("impossible de diviser par 0 \n");
                exit(-1);
            }
            break;
    }
}

float evaluer(Noeud* racine)
{
    float a,b;
    
    if((!racine->fg) && (!racine->fd))
        return((float)racine->val.operand);

    a = evaluer(racine->fg);
    b = evaluer(racine->fd);

    return((float)calculer(a,b,racine->val.operateur));
}