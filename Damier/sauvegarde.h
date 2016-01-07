//
//  sauvegarde.h
//  Damier
//
//  Created by Nicolas Loridon on 07/01/2016.
//  Copyright © 2016 Nicolas Loridon. All rights reserved.
//

#ifndef sauvegarde_h
#define sauvegarde_h

#include <stdio.h>

int save(int const damier[10][10],int const player,int const n_blanc,int const n_noir);
int load(int damier[10][10],int *player, int *n_blanc,int *n_noir);

#endif /* sauvegarde_h */
