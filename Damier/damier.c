//
//  damier.c
//  Damier
//  Implementation des fonctions du moteur de jeu.
//  Created by Nicolas Loridon on 07/01/2016.
//  Copyright © 2016 Nicolas Loridon. All rights reserved.
//

#include "damier.h"


//************************
//* Initialise le damier *
//************************
int init(int damier[10][10],int *player, int *n_blanc,int *n_noir)
{
    int i,j;
    
    //On met tout le damier a 0(vide)
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            damier[i][j]= 0;
        }
    }
    
    //On place les pions du joueur blanc en position debut de partie
    damier[0][0]=BLANC;
    damier[0][2]=BLANC;
    damier[0][4]=BLANC;
    damier[0][6]=BLANC;
    damier[0][8]=BLANC;
    damier[1][1]=BLANC;
    damier[1][3]=BLANC;
    damier[1][5]=BLANC;
    damier[1][7]=BLANC;
    damier[1][9]=BLANC;
    damier[2][0]=BLANC;
    damier[2][2]=BLANC;
    damier[2][4]=BLANC;
    damier[2][6]=BLANC;
    damier[2][8]=BLANC;
    damier[3][1]=BLANC;
    damier[3][3]=BLANC;
    damier[3][5]=BLANC;
    damier[3][7]=BLANC;
    damier[3][9]=BLANC;
    
    
    //De même avec les pions noir
    damier[9][1]=NOIR;
    damier[9][3]=NOIR;
    damier[9][5]=NOIR;
    damier[9][7]=NOIR;
    damier[9][9]=NOIR;
    damier[8][0]=NOIR;
    damier[8][2]=NOIR;
    damier[8][4]=NOIR;
    damier[8][6]=NOIR;
    damier[8][8]=NOIR;
    damier[7][1]=NOIR;
    damier[7][3]=NOIR;
    damier[7][5]=NOIR;
    damier[7][7]=NOIR;
    damier[7][9]=NOIR;
    damier[6][0]=NOIR;
    damier[6][2]=NOIR;
    damier[6][4]=NOIR;
    damier[6][6]=NOIR;
    damier[6][8]=NOIR;
    
    //On a placé 20 pions blanc et 20 pions noir, on affecte donc ces valeurs a n_blanc et n_noir
    *n_blanc =20;
    *n_noir=20;
    
    //Les blanc commencent
    *player=BLANC;
    
    return 1;
    
}

int initTest(int damier[10][10],int *player, int *n_blanc,int *n_noir)
{
    int i,j;
    
    //On met tout le damier a 0(vide)
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            damier[i][j]= 0;
        }
    }
    
    //On place les pions du joueur blanc en position debut de partie
    damier[3][1]=BLANC;
    damier[3][3]=DAME_BLANCHE;
    
    
    //De même avec les pions noir
   
    damier[6][0]=NOIR;
    damier[6][2]=DAME_NOIR;
    
    //On a placé 20 pions blanc et 20 pions noir, on affecte donc ces valeurs a n_blanc et n_noir
    *n_blanc =2;
    *n_noir=2;
    
    //Les blanc commencent
    *player=BLANC;
    
    return 1;
    
}

//********************************************************************
//* Compte les pions et raffraichie les compteur n_blanc et n_noir   *
//********************************************************************
void refreshCounter(int const damier[10][10],int *n_blanc,int *n_noir)
{
    *n_blanc=0;
    *n_noir =0;
    int i,j;
    for(i=0;i<10;i++)
        for(j=0;j<10;j++)
        {
            if (damier[i][j]==NOIR||damier[i][j]==DAME_NOIR)
                (*n_noir)++;
            else if(damier[i][j]==BLANC||damier[i][j]==DAME_BLANCHE)
                (*n_blanc)++;
        }
}


//************************
//* Affiche le damier   *
//************************
void display(int const damier[10][10]){
    int i,j;
    char sym;
    
    //Entete du damier
    printf("   ");
    for(i=0;i<10;i++)
        printf("%3d ",i);
    printf("\n   -----------------------------------------\n");
    
    //Contenu du damier
    for(i=0;i<10;i++)
    {
        printf("%2d |",i);
        for(j=0;j<10;j++)
        {
            if(damier[i][j] != 0)
            {
                if (damier[i][j]%2==0)
                    sym ='n';
                else
                    sym='b';
                
                if (damier[i][j]>2)
                    printf("[%c]",sym);
                else
                    printf(" %c ",sym);
                
                
            }
            else
                printf("   ");
            printf("|");
        }
        printf("\n   -----------------------------------------\n");
    }
}



//*******************************
//* Renvoi l'id de l'adversaire *
//*******************************
int opponent(int player)
{
    if(player == NOIR)
        return BLANC;
    if(player == BLANC)
        return NOIR;
    return -1;
}

//*************************************
//* Effectue le deplacement d'un pion *
//*************************************
void deplacePaws(int damier[10][10],int io,int jo,int id,int jd)
{
    damier[id][jd]=damier[io][jo]; //On copie le pion sur la case destination
    damier[io][jo] = 0;            //On supprime le pion sur la case d'origine.
}


/**********************************************************************************
 MovePawns test, puis effectue un déplacement, et retourne un etat restituant l'action accomplie:
 -1 mouvement hors damier
 -2 case destination occupée
 -3 le pion n'appartient pas au joueur
 -4 le joueur n'est ni Blanc ni Noir
 -10 le deplacement est invalide
 
 1 le pion a avancé
 2 le joueur a mangé un pion adverse
 3 le joueur atteint l'extremité du damier et obtient une dame
 4 le joueur a mangé un pion adverse, et a atteint l'extremité, il obtient aussi une reine
 ************************************************************************************/
int movePawns(int const player,int damier[10][10], int io,int jo, int id,int jd)
{
    int state=0;
    if (io <0 || io >9 ||
        id <0 || id >9)
        return -1;
    //On retourne -1 si le mouvement est hors du damier
    
    if (damier[id][jd] != 0)
        return -2;
    //On retourne -2 si la case destination est occupée
    // l'opération modulo permet de garder le test valide sur les reines.
    if (damier[io][jo]%2!=player%2)
        return -3;
    //On retourne -3 si le joueur ne selectionne pas un de ses pions
    
    if(player ==BLANC)
    {
        //Deplacement standard : une case en diagonal vers le bas
        if(id == io+1 && (jd == jo+1|| jd == jo-1))
        {
            deplacePaws(damier, io, jo, id, jd);
            state= 1;
        }
        
        //Deplacement de reine : une case en diagonal vers le bas
        else if(damier[io][jo]==DAME_BLANCHE && id == io-1 && (jd == jo+1|| jd == jo-1))
        {
            deplacePaws(damier, io, jo, id, jd);
            state= 1;
        }
        
        //Attaque Pion adverse bas/droite
        else if(id == io+2 && jd == jo+2 && damier[io+1][jo+1]%2 == 0)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io+1][jo+1]=0;
            state= 2;
        }
        //Attaque Pion adverse bas/gauche
        else if(id == io+2 && jd == jo-2 && damier[io+1][jo-1]%2 == 0)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io+1][jo-1]=0;
            state= 2;
        }
        //Attaque Pion adverse haut/gauche
        else if(id == io-2 && jd == jo-2 && damier[io-1][jo-1]%2 == 0)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io-1][jo-1]=0;
            state= 2;
        }
        //Attaque Pion adverse haut/droite
        else if(id == io-2 && jd == jo+2 && damier[io-1][jo+1]%2 == 0)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io-1][jo+1]= 0;
            state= 2;
        }
        else
            return -10;
        //On retourne -10 si le déplacement est inadmissble.
        
        //Si le joueur Blanc atteind la ligne 9
        if(id==9 && damier[id][jd]==BLANC)
            state+=2;
    }
    
    else if(player == NOIR)
    {
        
        //Deplacement standard : une case en diagonal vers le haut
        if(id == io-1 && (jd == jo+1|| jd == jo-1))
        {
            deplacePaws(damier, io, jo, id, jd);
            state= 1;
        }
        
        //Deplacement de reine : une case en diagonal vers le bas
        else if(damier[io][jo]==DAME_NOIR && id == io+1 && (jd == jo+1|| jd == jo-1))
        {
            deplacePaws(damier, io, jo, id, jd);
            state= 1;
        }
        
        //Attaque Pion adverse bas/droite
        else if(id == io+2 && jd == jo+2 && damier[io+1][jo+1]%2==1)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io+1][jo+1]=0;
            state= 2;
        }
        
        //Attaque Pion adverse bas/gauche
        else if(id == io+2 && jd == jo-2 && damier[io+1][jo-1]%2==1)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io+1][jo-1]=0;
            state= 2;
        }
        
        //Attaque Pion adverse haut/gauche
        else if(id == io-2 && jd == jo-2 && damier[io-1][jo-1]%2==1)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io-1][jo-1]=0;
            state= 2;
        }
        
        //Attaque Pion adverse haut/droite
        else if(id == io-2 && jd == jo+2 && damier[io-1][jo+1]%2==1)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io-1][jo+1]= 0;
            state= 2;
        }
        else
            return -10;
        //On retourne -10 si le déplacement est inadmissble
        
        //Si le joueur NOIR atteint la ligne 0, il obtiendra une REINE_NOIR
        if(id==0 && damier[id][jd]==NOIR)
            state+=2;
    }
    else
        return -4;
    //On retourne -4 si le joueur n'est ni BLANC ni NOIR
    
    
    //Les lignes suivante s'executent si il n'y a eu aucune erreur rencontrés ci dessus
    
    //On attribue une reine si les conditions sont respectées
    if(state>2 && player == NOIR)
        damier[id][jd]=DAME_NOIR;
    if(state>2 && player ==BLANC)
        
        damier[id][jd]=DAME_BLANCHE;
    //On renvoi l'etat restituant l'action accomplie
    return state;
    
}


//***************************************
//* Décrit l'action associé a un etat   *
//***************************************
void describeState(int const player,int const state){
    char *splayer;
    if(player==NOIR)
        splayer="Noir";
    else
        splayer="Blanc";
    switch (state) {
        case -1:
            printf("----------\nMouvement hors damier\n----------\n");
            break;
        case -2:
            printf("----------\nCase destination occupée\n----------\n");
            break;
        case -3:
            printf("----------\nLe pion selectionné n'est pas %s\n----------\n",splayer);
            break;
        case -4:
            printf("----------\nIl n'y a pas de joueur courant, redemmarez\n----------\n");
            break;
        case -10:
            printf("----------\nMouvement impossible\n----------\n");
            break;
        case 1:
            printf("----------\nUn pion %s avance\n----------\n",splayer);
            break;
        case 2:
            printf("----------\nUn pion %s et mange un pion adverse.\n----------\n",splayer);
            break;
        case 3:
            printf("----------\nJoueur %s obtient une reine.\n----------\n",splayer);
            break;
        case 4:
            printf("----------\nLes %s mange un adversaire et obtiennent une reine\n----------\n",splayer);
            break;
        default:
            printf("Il semble qu'il y ait eu une erreur, redemarrez");
            break;
    }
}
