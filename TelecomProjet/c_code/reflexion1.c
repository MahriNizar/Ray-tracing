#include "reflexion1.h"
#include <stdio.h>

double reflexion_1(Wall *wall_list,Coordinates *tx,Coordinates *rx,int wall_count){
    //Calcul la puissance reçue par rx par émission de tx,en fonction d'une 
    //quelconque réflexion possible avec les obstacles de wall_list
    double P =0;
    
    for (int i=0; i<wall_count;i++){
        
        if (is_reflexion(&wall_list[i],tx,rx)){
            //vérifie si réflexion possible 
            Coordinates ri = point_image(&wall_list[i],tx);
            Coordinates vect_d = diff_p(rx,&ri);
            IntersectionResult intersect_data = intersection(&wall_list[i],&vect_d,&ri);
            if (intersect_data.is_intersect){
                double complex R = coef_reflexion(&wall_list[i],&vect_d);
                double complex T1 = transmission(wall_list,tx,&intersect_data.p,wall_count);
                double complex T2 = transmission(wall_list,&intersect_data.p,rx,wall_count);
                double complex E = T2*T1*R*csqrt(10.2)*cexp(-wall_list[0].beta*norme(vect_d)*I)/norme(vect_d);
                //10.2 : valeur précalculée de sqrt(60PeG_max)=sqrt(6à*1.7*0.1)
                P+= pow((cabs(E)),2);
            }
        }
    }
    return P;
}