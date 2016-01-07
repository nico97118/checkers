//
//  main.c
//  Jeu de dames | EFREI projet L1
//  Fichier principal
//  Created by Nicolas Loridon on 07/01/2016.
//  Copyright © 2016 Nicolas Loridon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "damier.h"
#include "sauvegarde.h"



//Siffler n'est pas jouer
//Il faut écrire une fonction qui prend un argument le damier et le joueur.
//Si player peut attaquer un pion adverse. Alors il doit attaquer l'un d'entre eux


//Prototype du menu implementé sous la fonction main()
int menu(int damier[10][10],int *player, int *n_blanc,int *n_noir);
int play(int damier[10][10],int const player);

//*************************
//*Fonction principale    *
//*************************
int main(int argc, const char * argv[]) {
    
    //Initialisation des variables
    
    int damier[10][10];
    //le joueur courant
    int player;
    //Le nombre de pion sur le plateau
    int n_blanc,n_noir;
    //variable d'etat qui permet de décrire la derniere action
    int state;
    
    //Menu principale
    menu(damier, &player,&n_noir,&n_blanc);

    //************************
    //* Boucle de la partie  *
    //************************
    do{
        
        display(damier);            //On affiche le damier
        
        if (player ==BLANC)         //On affiche le joueur courant
            printf("----------\nLes Blancs jouent.\n----------\n");
        if (player == NOIR)
            printf("----------\nLes Noirs jouent.\n----------\n");
        
        //Faire:
        do{
            //Le joueur courant fait son coup
            state = play(damier, player);
            
            //On décrit ce qu'il se passe.
            describeState(player,state);
        
        }while(state<1);  //Tant que l'etat ne décrit pas un deplacement valide.
        
        //Si l'etat décrit l'attaque d'un pion adverse, on raffraichit les compteurs
        if(state==2 || state ==4)
        {
            refreshCounter(damier,&n_blanc,&n_noir);
        }
        player=opponent(player);                //On change de joueur
        save(damier,player,n_blanc,n_noir);     //On sauvegarde après chaque coup.(peut evoluer)
    
    }while(n_blanc>0 && n_noir >0);             //Tant qu'il reste des pions blancs et noir
    
    //Annonce du Vainqueur
    //....
    
    display(damier);
}

//************************
//* Menu principal       *
//************************
int menu(int damier[10][10],int *player, int *n_blanc,int *n_noir)
{
    int choix;
    
    printf("***************\nJeu de Dames\n****************\n\n");
    printf("1. Nouvelle partie \n2.Charger\n3.Debug/Test\n");
    do{
        scanf("%d",&choix);
        switch (choix) {
            case 1:     //1. On creer une nouvelle partie en initialisant le damier
                init(damier,player,n_blanc,n_noir);
                return 1;
                break;
            case 2:
                //2. on charge la partie sauvegardée dernierement.
                if(load(damier,player,n_blanc,n_noir) == -1)
                    return EXIT_FAILURE;
                return 2;
                break;
            case 3:
                initTest(damier, player, n_blanc, n_noir);
                return 3;
                break;
            default:
                printf("Choix incorrect\n\n");
                break;
        }
    }while(!(choix==1||choix==2));
    
    return 0;
}

//*********************************************
//* Play permet a "player" de tenter son coup *
//*********************************************
int play(int damier[10][10],int const player)
{
    int xo,yo,xd,yd;
    
    //Aquisition de l'origine
    printf("\n\nSelection de votre pion [x y]:\n");
    scanf("%d %d",&xo,&yo);
    
    //Aquisition de la destination
    printf("\nSelection de sa destination[x y]:\n");
    scanf("%d %d",&xd,&yd);
    
    //On test, et si possible, effectue le déplacement.
    return movePawns(player, damier, yo, xo, yd, xd);
}


