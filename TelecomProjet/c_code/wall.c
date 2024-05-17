#include "wall.h"
#include <complex.h>
#include <math.h>
#include <stdio.h>
#define PI 3.14159265359

Wall create_wall(Coordinates pos_debut, Coordinates pos_end, float width, float rel_perm, float conductivity) {
    Wall wall;
    wall.mu0 = 4 * PI * 1e-7;
    wall.eps0 = 8.8541878 * 1e-12;
    wall.w = 2 *PI * 6 * 1e9;
    wall.beta = wall.w / 299792458;
    wall.pos_debut = pos_debut;
    wall.pos_end = pos_end;
    wall.width = width;
    wall.rel_perm = rel_perm;
    wall.conductivity = conductivity;

    // calcule des différents éléments vectoriels du mur
    
    wall.wall_vector = diff(pos_end,pos_debut);
    wall.norme = norme(wall.wall_vector);
    wall.unit_dir.x = wall.wall_vector.x / wall.norme;
    wall.unit_dir.y = wall.wall_vector.y / wall.norme;
    wall.unit_normal.x = wall.unit_dir.y;
    wall.unit_normal.y = -wall.unit_dir.x;

    // Calcule gamma, hypothèses pertes faibles dans matériau pour avoir résultat similaire au tp 4.
    wall.gamma = wall.w * I * csqrt(wall.mu0 *((rel_perm * wall.eps0) - (wall.conductivity / wall.w)*I ));
    wall.impedance = csqrt(wall.mu0/((rel_perm * wall.eps0)-I*(wall.conductivity / wall.w)));
    return wall;
}

double point_intersection(Wall *wall,Coordinates *d, Coordinates *tx) {
    //méthode permettant de calculer le point d'intersection
    double t;
    double divisor = d->y * wall->unit_dir.x - d->x * wall->unit_dir.y;

    if (divisor == 0) {
        t = 0;
    } else {
        t = (d->y * (tx->x - wall->pos_debut.x) - d->x * (tx->y - wall->pos_debut.y)) / divisor;
    }
    
    return t;
}

IntersectionResult intersection( Wall *wall,Coordinates *d,Coordinates *tx) {
    //structure reprenant les valeurs du point d'intersection
    
    double t = point_intersection(wall,d, tx );
    
    Coordinates scaled_unit_dir = scal(wall->unit_dir, t);
    Coordinates p = somme(wall->pos_debut, scaled_unit_dir);
    
    IntersectionResult result;
    result.t = t;
    result.p = p;

    if (t < wall->norme && t > 0) {
        result.is_intersect = 1;/*1 = True*/
        
    } else {
        result.is_intersect = 0;
    }

    return result;
}