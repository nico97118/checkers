//
//  CPU.c
//  Damier
//
//  Created by Nicolas Loridon on 08/01/2016.
//  Copyright © 2016 Nicolas Loridon. All rights reserved.
//

#include "CPU.h"

int playCPU(int damier[10][10],int player,int attack)
{
    int i,j;
    int mustAttack=0,state=0,rafle=0;
    
    do{
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if ((damier[i][j]==player || damier[i][j]==player+2) && detectAttack(damier, j, i, player)>0)
            {
                state = movePawns(player, damier, mustAttack, i, j, i+2, j+2);
                if(state<1)
                    state = movePawns(player, damier, mustAttack, i, j, i+2, j-2);
                if(state<1)
                    state = movePawns(player, damier, mustAttack, i, j, i-2, j-2);
                if(state<1)
                    state = movePawns(player, damier, mustAttack, i, j, i+2, j-2);
                

            }
            if (state>0)
                break;
        }
        if (state>0)
            break;
    }
    //On a tenté toutes les attaques possibles.
    
    if (state<1) {
        for (i=0; i<10; i++) {
            for (j=0; j<10; j++) {
                if(damier[i][j]== player || damier[i][j] == player+2)
                {
                    state = movePawns(player, damier, mustAttack, i, j, i+1, j+1);
                    if(state<1)
                        state = movePawns(player, damier, mustAttack, i, j, i+1, j-1);
                    if(state<1)
                        state = movePawns(player, damier, mustAttack, i, j, i-1, j-1);
                    if(state<1)
                        state = movePawns(player, damier, mustAttack, i, j, i-1, j+1);
                }
                if (state>0)
                    break;
            }
            if (state>0)
                break;
        }
    }
    }while(state<1);
    
    
    
    return state;
}