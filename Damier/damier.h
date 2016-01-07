//
//  damier.h
//  Damier
//  Moteur de jeu pour le Jeu de Dame
//  Created by Nicolas Loridon on 07/01/2016.
//  Copyright © 2016 Nicolas Loridon. All rights reserved.
//

#ifndef damier_h
#define damier_h
#define BLANC 1
#define NOIR 2
#define DAME_NOIR 4
#define DAME_BLANCHE 3


#include <stdio.h>

int init(int damier[10][10],int *player, int *n_blanc,int *n_noir);
int initTest(int damier[10][10],int *player, int *n_blanc,int *n_noir);
int opponent(int player);
void display(int const damier[10][10]);
void deplacePaws(int damier[10][10],int io,int jo,int id,int jd);
int movePawns(int const player,int damier[10][10],int mustAttack, int io,int jo, int id,int jd);
void describeState(int const player,int const state);
void refreshCounter(int const damier[10][10],int *n_blanc,int *n_noir);
int detectAttack(int const damier[10][10],int const x,int const y,int const player);
int detectAttackGlobal(int damier[10][10],int player);

#endif /* damier_h */
