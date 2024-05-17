#ifndef FONCTIONS_CALCUL_H
#define FONCTIONS_CALCUL_H
#include <stdio.h>
#include "wall.h"
#include <complex.h>
#include <stdlib.h>
double cos_angle_i(Wall *wall,Coordinates *d);
double sin_angle_i(Wall *wall,Coordinates *d);
double sin_angle_t(Wall *wall,Coordinates *d);
double cos_angle_t(Wall *wall,Coordinates *d);
double propag_mur(Wall *wall,Coordinates *d);
char is_reflexion(Wall *wall,Coordinates *tx,Coordinates *rx );
Coordinates point_image(Wall *wall,Coordinates *tx);
double complex coef_reflexion(Wall *wall,Coordinates *d);
double complex coeff_reflexion_perp(Wall *wall,Coordinates *d);
double complex coef_transmission(Wall *wall,Coordinates *d);
double complex transmission(Wall *wall_list,Coordinates *tx,Coordinates *rx,int wall_count);














#endif