//
//  sauvegarde.c
//  Damier
//
//  Created by Nicolas Loridon on 07/01/2016.
//  Copyright © 2016 Nicolas Loridon. All rights reserved.
//

#include "sauvegarde.h"

//*************************
//* Sauvegarde la partie  *
//*************************
int save(int const damier[10][10],int const player,int const n_blanc,int const n_noir)
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
