//
//  main.c
//  Jeu de dames | EFREI projet L1
//
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
    //variable de decision
    int xo,yo,xd,yd;
    //variable d'etat qui permet de décrire la derniere action
    int state;
    
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
        
        }while(state<1);                        //Tant que l'etat ne décrit pas un deplacement valide.
        
        player=opponent(player);                //On change de joueur
        save(damier,player,n_blanc,n_noir);     //On sauvegarde après chaque coup.(peut evoluer)
        
    
    }while(n_blanc>0 || n_noir >0);             //Tant qu'il reste des pions blancs ou noir
    
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
    printf("1. Nouvelle partie \n2.Charger\n");
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
            default:
                printf("Choix incorrect");
                break;
        }
    }while(!(choix==1||choix==2));
    
    return 0;
}


