#include <stdio.h>
#include "appart_layout.h"
#define WHITE_WALL_WIDTH 0.3
#define WHITE_WALL_REL_PERM 6.4954//5.5 valeur 6GHz
#define WHITE_WALL_CONDUCTIVITY 1.43 //0.0501 valeur 6GHz

#define RED_WALL_WIDTH 0.1
#define RED_WALL_REL_PERM 2.7//2.02 valeur 6GHz
#define RED_WALL_CONDUCTIVITY 0.178// 0.0148 valeur 6GHz

#define METAL_WALL_WIDTH 0.05
#define METAL_WALL_REL_PERM 1
#define METAL_WALL_CONDUCTIVITY 10000000

#define GLASS_WALL_WIDTH 0.05
#define GLASS_WALL_REL_PERM 6.3919
#define GLASS_WALL_CONDUCTIVITY 0.00107


void init_walls(Wall *wall_list, int *wall_count, char elevator) {
    //Fonction permettant d'initialiser les murs et ses valeurs dépendantes, 
    //ainsi que la liste des récepteurs avec leurs coordonnées respectives
    // Condition prenant en compte la présence de l'ascenseur est défini ici aussi
    
    double white_wall[][4] = {{0, 0, 6, 0}, {4, 0, 4.001, 2.001}, {4.001, 2, 9, 2}, {9, 0, 9, 2}, {9, 0, 12, 0}, {15, 4, 15, 8}, {0, 0, 0, 8}, {0, 8, 15, 8}, {7, 4, 7, 8}};
    double red_wall[][4] = {{0, 3, 4, 3}, {4, 4, 4, 8}, {4, 4, 5, 4}, {6, 4, 9, 4}, {10, 4, 11, 4}, {11, 4, 11, 8}};
    double glass_wall[] = {12, 0, 15, 4};
    double metal_wall[] = {6, 0, 6, 2};
    
    int i;int j;
    double xr;double yr;int count =0;
    
    for (i = 0; i < 9; i++) {
        wall_list[*wall_count] = create_wall(create_coo(white_wall[i][0],white_wall[i][1]), create_coo(white_wall[i][2],white_wall[i][3]), WHITE_WALL_WIDTH, WHITE_WALL_REL_PERM, WHITE_WALL_CONDUCTIVITY);
        (*wall_count)++;
    }

    
    for (i = 0; i < 6; i++) {
        wall_list[*wall_count] = create_wall(create_coo(red_wall[i][0],red_wall[i][1]), create_coo(red_wall[i][2],red_wall[i][3]), RED_WALL_WIDTH, RED_WALL_REL_PERM, RED_WALL_CONDUCTIVITY);
        (*wall_count)++;
    }


    wall_list[*wall_count] = create_wall(create_coo(metal_wall[0], metal_wall[1]), create_coo(metal_wall[2], metal_wall[3]), METAL_WALL_WIDTH, METAL_WALL_REL_PERM, METAL_WALL_CONDUCTIVITY);
    (*wall_count)++;

    
    wall_list[*wall_count] = create_wall(create_coo(glass_wall[0], glass_wall[1]), create_coo(glass_wall[2], glass_wall[3]), GLASS_WALL_WIDTH, GLASS_WALL_REL_PERM, GLASS_WALL_CONDUCTIVITY);
    (*wall_count)++;

    if (elevator){
        double elevator_wall[][4] = {{4.1,0.1,4.1,1.8},{4.1,1.8,5.9,1.8},{4.1,0.1,5.9,0.1},{5.9,0.1,5.9,1.8}};
        for (i = 0; i < 4; i++) {
        wall_list[*wall_count] = create_wall(create_coo(elevator_wall[i][0],elevator_wall[i][1]), create_coo(elevator_wall[i][2],elevator_wall[i][3]), METAL_WALL_WIDTH, METAL_WALL_REL_PERM, METAL_WALL_CONDUCTIVITY);
        (*wall_count)++;
    }
    }

    
}