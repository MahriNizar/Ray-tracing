#include "wall.h"
#include <stdio.h>
#include "coordinates.h"
#include "appart_layout.h"
#include "fonctions_calcul.h"
#include "reflexion0.h"
#include "reflexion1.h"
#include "reflexion2.h"
#define ELEV 0

//pour initier la shard_library :
//gcc -std=c11 -shared -o main.so main.c wall.c coordinates.c appart_layout.c 
//fonctions_calcul.c reflexion0.c reflexion1.c reflexion2.c 

double main(double rx_x,double rx_y,double tx_x,double tx_y){
    //fonction main appelé dans le code python
    //prend en entrée un émetteur et un récepteur et renvoie la puissance calculée 
    double P_0 =0;double P_1=0;double P_2=0;
    Wall wall_list[17+4*ELEV]; //initialise la liste des murs
    int wall_count = 0;
    Coordinates emetteur =create_coo(tx_x,tx_y);
    Coordinates recepteur =create_coo(rx_x,rx_y);
    init_walls(wall_list, &wall_count,ELEV);
    //calcul la puissance par les effet de reflexions et transmission
    P_0 = reflexion_0(wall_list,&emetteur,&recepteur, wall_count);
    P_1 = reflexion_1(wall_list,&emetteur,&recepteur, wall_count);
    P_2 =reflexion_2(wall_list,&emetteur,&recepteur, wall_count);
    double P_tot = P_0+P_1+P_2;
    return P_tot;
}

