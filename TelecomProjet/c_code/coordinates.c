#include "coordinates.h"

double norme(Coordinates c){
    //calcule et renvoie la norme d'un vecteur
    return sqrt(c.x * c.x + c.y * c.y);
}

Coordinates create_coo(double x1,double y1){
    //crée et renvoie une struct coordinates en fonction de 
    //deux points
    Coordinates coo;
    coo.x = x1;
    coo.y = y1;
    return coo;
}

double distance(Coordinates c1,Coordinates c2){
    //calcul et renvoie la distance séparant 2 points
    return sqrt((c1.x-c2.x)*(c1.x-c2.x) +(c1.y-c2.y)*(c1.y-c2.y) );

}

Coordinates somme(Coordinates c1, Coordinates c2){
    //calcul la somme de deux coordonnées et renvoie une struct 
    //reprenant le résultat
    Coordinates somme;
    somme.x = c1.x+c2.x;
    somme.y = c1.y+c2.y;
    return somme;
}

Coordinates diff(Coordinates c1, Coordinates c2){
    //calcul la différence de deux coordonnées et renvoie une struct reprenant le résultat
    Coordinates diff;
    diff.x = c1.x-c2.x;
    diff.y = c1.y-c2.y;
    return diff;
}

Coordinates scal(Coordinates c1, double a){
    //calcul le produit d'une coordonnées avec une constante et renvoie une struct reprenant le résultat
    Coordinates scal;
    scal.x = a*c1.x;
    scal.y = a*c1.y;
    return scal;
}
double prod_scal(Coordinates c1, Coordinates c2){
    //calcul le produit de deux coordonnées et renvoie le résultat
    return (c1.x*c2.x +c1.y*c2.y);
}
double norme_p(Coordinates *c){
    //calcul la norme d'un vecteur pointeur
    return sqrt(c->x * c->x + c->y * c->y);
}
Coordinates diff_p(Coordinates *c1,Coordinates *c2){
    //calcul la différence de deux pointeurs de coordonnées et renvoie une struct reprenant le résultat
    Coordinates diff;
    diff.x = c1->x-c2->x;
    diff.y = c1->y-c2->y;
    return diff;

}
Coordinates diff_p1(Coordinates *c1,Coordinates c2){
    //calcul la différence d'un pointeurs de coordonnées et une autre coordonnées et renvoie une struct reprenant le résultat
    Coordinates diff;
    diff.x = c1->x-c2.x;
    diff.y = c1->y-c2.y;
    return diff;
}
double distance_p(Coordinates *c1,Coordinates c2){
    //calcul la distance d'un pointeurs de coordonnées et une autre coordonnées et renvoie une struct reprenant le résultat
    return sqrt((c1->x-c2.x)*(c1->x-c2.x) +(c1->y-c2.y)*(c1->y-c2.y) );
}
Coordinates scal_p(Coordinates *c1, double a){
    //calcul le produit d'un un pointeur de coordonnées avec une constante et renvoie une struct reprenant le résultat
    Coordinates scal;
    scal.x = a*c1->x;
    scal.y = a*c1->y;
    return scal;
}