#ifndef COORDINATES_H
#define COORDINATES_H
#include <math.h>

//Définis la structure Coordinates qui permet de facilement interagir avec les coordonnées des différentes valeurs.

typedef struct {
    double x;
    double y;
} Coordinates;

double norme(Coordinates c);
double distance(Coordinates c1,Coordinates c2);
Coordinates somme(Coordinates c1, Coordinates c2);
Coordinates diff(Coordinates c1, Coordinates c2);
Coordinates scal(Coordinates c1, double a);
double prod_scal(Coordinates c1, Coordinates c2);
Coordinates create_coo(double x1,double y1);


double norme_p(Coordinates *c);
double distance_p(Coordinates *c1,Coordinates c2);
Coordinates diff_p(Coordinates *c1,Coordinates *c2);
Coordinates scal_p(Coordinates *c1, double a);


Coordinates diff_p1(Coordinates *c1,Coordinates c2);

#endif