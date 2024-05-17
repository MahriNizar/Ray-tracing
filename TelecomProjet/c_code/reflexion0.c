#include "reflexion0.h"
#include <stdio.h>

double reflexion_0(Wall *wall_list,Coordinates *tx,Coordinates *rx,int wall_count){
    // Calcul la puissance reçue par rx par émission par tx et prend en compte les quelconques 
    //obstacles de wall_list
    Coordinates vect_d = diff_p(rx,tx);
    double complex T = transmission(wall_list,tx,rx,wall_count);
    double complex E = T*sqrt(10.2)*cexp(-wall_list[0].beta*norme(vect_d)*I)/norme(vect_d);
    //10.2 : valeur précalculée de sqrt(60PeG_max)=sqrt(6à*1.7*0.1)
    double P = pow(cabs(E),2);
    
    return P;

}