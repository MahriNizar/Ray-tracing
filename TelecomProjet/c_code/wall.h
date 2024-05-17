#ifndef WALL_H
#define WALL_H

#include "coordinates.h"
#include <complex.h>

typedef struct {
    double mu0;
    double eps0;
    double w;
    double beta;
    Coordinates pos_debut;
    Coordinates pos_end;
    float width;
    float rel_perm;
    float conductivity;
    Coordinates wall_vector;
    double norme;
    Coordinates unit_dir;
    Coordinates unit_normal;
    double complex alpham;
    double complex betam;
    double complex gamma;
    double complex  impedance;
} Wall;

typedef struct {
    char is_intersect;
    double t;
    Coordinates p;
} IntersectionResult;

Wall create_wall(Coordinates pos_debut, Coordinates pos_end, float width, float rel_perm, float conductivity);
double point_intersection(Wall *wall, Coordinates *d, Coordinates *tx);
IntersectionResult intersection(Wall *wall, Coordinates *d, Coordinates *tx);



#endif