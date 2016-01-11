//
//  main.c
//  Jeu de dames | EFREI projet L1
//  Fichier principal
//  Created by Nicolas Loridon on 07/01/2016.
//  Copyright © 2016 Nicolas Loridon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "sauvegarde.h"
#include "CPU.h"




//Siffler n'est pas jouer
//Il faut écrire une fonction qui prend un argument le damier et le joueur.
//Si player peut attaquer un pion adverse. Alors il doit attaquer l'un d'entre eux


//Prototype du menu implementé sous la fonction main()
int menu(int damier[10][10],int *player, int *n_blanc,int *n_noir,int *CPU);
int play(int damier[10][10],int const player,int attack);
int menuNewGame();

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
    int CPU=0,state,mustAttack;
    
    //Menu principale
    if(menu(damier, &player,&n_noir,&n_blanc,&CPU)==10)
        CPU=1;
    
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
            //On regarde si une attaque est possible
            mustAttack=detectAttackGlobal(damier, player);
            
            //Le joueur courant fait son coup
            if(player==BLANC||(player==NOIR && CPU==0))
                state = play(damier, player,mustAttack);
            else
                state = playCPU(damier, player, mustAttack);
            
            //On décrit ce qu'il se passe.
            describeState(player,state);
        
        }while(state<1);  //Tant que l'etat ne décrit pas un deplacement valide.
        
        //Si l'etat décrit l'attaque d'un pion adverse, on raffraichit les compteurs
        if(state==2 || state ==4)
        {
            refreshCounter(damier,&n_blanc,&n_noir);
        }
        player=opponent(player);                //On change de joueur
        save(damier,player,n_blanc,n_noir,CPU);     //On sauvegarde après chaque coup.(peut evoluer)
    
    }while(n_blanc>0 && n_noir >0);             //Tant qu'il reste des pions blancs et noir
    
    if(n_blanc>0)
        printf("Les blancs gagnent");
    else
        printf("les noirs gagnent");
}

//************************
//* Menu principal       *
//************************
int menu(int damier[10][10],int *player, int *n_blanc,int *n_noir,int *CPU)
{
    int choix;
    
    printf("***************\nJeu de Dames\n****************\n\n");
    printf("1. Nouvelle partie \n2.Charger\n3.Debug/Test\n");
    do{
        scanf("%d",&choix);
        switch (choix) {
            case 1:     //1. On creer une nouvelle partie en initialisant le damier
                init(damier,player,n_blanc,n_noir);
                if(menuNewGame()==2)
                    return 10;
                return 1;
                break;
            case 2:
                //2. on charge la partie sauvegardée dernierement.
                if(load(damier,player,n_blanc,n_noir,CPU) == -1)
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
    }while(!(choix==1||choix==2||choix==3));
    
    return 0;
}

int menuNewGame()
{
    
    int choix;
    do{
    printf("Jouer contre :\n\n1.Humain\n2.CPU\n");
    scanf("%d",&choix);
    switch (choix) {
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        default:
            printf("Choix incorrect\n");
            break;
    }
    }while(!(choix==1||choix==2));
    return -1;
}


//*********************************************
//* Play permet a "player" de tenter son coup *
//*********************************************
int play(int damier[10][10],int const player,int attack)
{
    int xo,yo,xd,yd;
    int state,mustAttack=0,rafle=0;
    do{
        if(rafle==0)
        {
            //Aquisition de l'origine
            printf("\n\nSelection de votre pion [x y]:\n");
            scanf("%d %d",&xo,&yo);
        }
        
        //Aquisition de la destination
        printf("\nSelection de sa destination[x y]:\n");
        scanf("%d %d",&xd,&yd);
        
        // Si on est en rafle, ou qu'une attaque est possible
        if(attack ==1 || rafle ==1)
            mustAttack = 1;  //Alors il faut attaquer
        
        //On test, et si possible, effectue le déplacement.
        state = movePawns(player, damier,mustAttack, yo, xo, yd, xd);
        rafle=0;
        if (((state==2||state==4)&&detectAttack(damier, xd, yd, player)>0)||(state==-11 && detectAttack(damier, xo, yo, player)>0))
        {
            rafle=1;
            describeState(player, state);
            display(damier);
            
            //Si il y'a eu erreur de saisie, on recommence la saisie depuis la même position
            if(state!=-11){
                xo=xd;
                yo=yd;
            }
            printf("***\nVous jouez le pion en [%d %d]\n***\n",xo,yo);
            
            //Trace pour debug
            //printf("detectattack :%d -*- state: %d \n",detectAttack(damier, xd, yd, player),state);

        }
    }while(rafle==1);
    return state;
}


