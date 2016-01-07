//
//  main.c
//  Jeu de dames | EFREI projet L1
//
//  Created by Nicolas Loridon on 07/01/2016.
//  Copyright © 2016 Nicolas Loridon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define BLANC 1
#define NOIR 2
#define DAME_NOIR 4
#define DAME_BLANCHE 3

//************************
//* Initialise le damier *
//************************
int init(int damier[10][10])
{
    int i,j;
    
    //On met tout le tableau a 0
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

    
    
    return 1;
    
}
//Renvoi l'id de l'adversaire de player.
int opponent(int player)
{
    if(player == NOIR)
        return BLANC;
    if(player == BLANC)
        return NOIR;
    return -1;
}

//************************
//* Afficher le damier   *
//************************
void display(int damier[10][10]){
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

//Deplace un pion
void deplacePaws(int damier[10][10],int io,int jo,int id,int jd)
{
    damier[id][jd]=damier[io][jo];
    damier[io][jo] = 0;
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
        else if(id == io+2 && jd == jo+2 && damier[io+1][jo+1]==NOIR)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io+1][jo+1]=0;
            state= 2;
        }
        //Attaque Pion adverse bas/gauche
        else if(id == io+2 && jd == jo-2 && damier[io+1][jo-1]==NOIR)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io+1][jo-1]=0;
            state= 2;
        }
        //Attaque Pion adverse haut/gauche
        else if(id == io-2 && jd == jo-2 && damier[io-1][jo-1]==NOIR)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io-1][jo-1]=0;
            state= 2;
        }
        //Attaque Pion adverse haut/droite
        else if(id == io-2 && jd == jo+2 && damier[io-1][jo+1]==NOIR)
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
        else if(id == io+2 && jd == jo+2 && damier[io+1][jo+1]==BLANC)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io+1][jo+1]=0;
            state= 2;
        }
    
        //Attaque Pion adverse bas/gauche
        else if(id == io+2 && jd == jo-2 && damier[io+1][jo-1]==BLANC)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io+1][jo-1]=0;
            state= 2;
        }
    
        //Attaque Pion adverse haut/gauche
        else if(id == io-2 && jd == jo-2 && damier[io-1][jo-1]==BLANC)
        {
            deplacePaws(damier, io, jo, id, jd);
            damier[io-1][jo-1]=0;
            state= 2;
        }
    
        //Attaque Pion adverse haut/droite
        else if(id == io-2 && jd == jo+2 && damier[io-1][jo+1]==BLANC)
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
void describeState(int player,int state){
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

//*************************
//* Sauvegarde la partie  *
//*************************
int save(int damier[10][10],int player,int n_blanc,int n_noir)
{
    int i,j;
    FILE* f = fopen("game.dat", "w"); //On ouvre le fichier game.dat en écriture, si il n'existe pas, on le crée
    fputc(player, f);                 //On écrit le joueur qui avait la main.
    fputc(n_blanc,f);                 //On écrit le nombre de pions blanc restant
    fputc(n_noir,f);                  //On écrit le nombre de pions noir restant
    for(i=0;i<10;i++)
        for(j=0;j<10;j++)
            fputc(damier[i][j], f);  //On écrit chaque case du tableau dans le fichier
    fclose(f);                       //Puis on ferme le fichier.
    return 1;
}

//********************************
//* Charger la derniere partie   *
//********************************
int load(int damier[10][10],int *player, int *n_blanc,int *n_noir)
{
    int i,j;
    FILE* f = fopen("game.dat", "r");  //On ouvre le fichier game.dat en lecture
    if(f!= NULL){                      //Si il n'y a pas d'erreur :
        *player = fgetc(f);              //le 1er caractere designe le joueur qui avait la main
        *n_blanc = fgetc(f);           //le 2eme , le nombre de pions blanc restant
        *n_noir = fgetc(f);             //le 3eme, le nombre de pions noir restant
        for(i=0;i<10;i++)
            for(j=0;j<10;j++)
                damier[i][j]= fgetc(f); //On récupere une a une les cases du damier sauvegardées.
        
        fclose(f);                      //Puis on ferme le fichier.
        return 1;   //On retourne 1 pour dire que tout s'est bien passé
    }
    else{
        printf("Erreur lors de l'ouverture du fichier\n");
        return -1;
    }
}

//Siffler n'est pas jouer
//Il faut écrire une fonction qui prend un argument le damier et le joueur.
//Si player peut attaquer un pion adverse. Alors il doit attaquer l'un d'entre eux




//*************************
//*Fonction principale    *
//*************************
int main(int argc, const char * argv[]) {
    
    //Initialisation des variables
    
    int damier[10][10];
    //le joueur courant
    int player = NOIR;
    //Le nombre de pion sur le plateau
    int n_blanc = 20,n_noir =20;
    //variable de decision
    int xo,yo,xd,yd;
    //variable d'etat qui permet de décrire la derniere action
    int state;
    int choix;
    
    //************************
    //* Menu principal       *
    //************************
    printf("***************\nJeu de Dames\n****************\n\n");
    printf("1. Nouvelle partie \n2.Charger\n");
    do{
        scanf("%d",&choix);
        switch (choix) {
            case 1:     //1. On creer une nouvelle partie en initialisant le damier
                init(damier);
                break;
            case 2:
                //2. on charge la partie sauvegardée dernierement.
                if(load(damier,&player,&n_blanc,&n_noir) == -1)
                    return EXIT_FAILURE;
                break;
            default:
                printf("Choix incorrect");
                break;
        }
    }while(choix<1 && choix>2);

    //************************
    //* Boucle de la partie  *
    //************************
    do{
        player=opponent(player);    //On change de joueur
        display(damier);            //On affiche le damier
        
        if (player ==BLANC)         //On affiche le joueur courant
            printf("----------\nLes Blancs jouent.\n----------\n");
        if (player == NOIR)
            printf("----------\nLes Noirs jouent.\n----------\n");
        
        //Faire:
        do{
            //Aquisition de l'origine
            printf("\n\nSelection de votre pion [x y]:\n");
            scanf("%d %d",&xo,&yo);
            //Aquisition de la destination
            printf("\nSelection de sa destination[x y]:\n");
            scanf("%d %d",&xd,&yd);
        
            //On test, et si possible, effectue le déplacement.
            state = movePawns(player, damier, yo, xo, yd, xd);
            //On décrit ce qu'il se passe.
            describeState(player,state);
            
            //Si l'etat décrit l'attaque d'un pion adverse, on inpute 1 au nb de pion de l'adversaire.
            if(state==2 || state ==4)
            {
                if(player==BLANC)
                    n_noir--;
                else
                    n_blanc--;
            }
        
        }while(state<1);        //Tant que l'etat ne décrit pas un deplacement valide.
        
        save(damier,player,n_blanc,n_noir);    //On sauvegarde après chaque coup.(Parti pris qui peut evoluer)
    
    }while(n_blanc>0 || n_noir >0);     //Tant qu'il reste des pions blancs ou noir
    
    //Annonce du Vainqueur
    //....
    
    display(damier);
}


