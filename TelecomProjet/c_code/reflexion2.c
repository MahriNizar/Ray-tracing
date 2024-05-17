#include "reflexion2.h"
#include <stdio.h>

double reflexion_2(Wall *wall_list,Coordinates *tx,Coordinates *rx,int wall_count){
    //Calcul la puissance reçue par rx par émission de tx,en fonction de 
    //quelconques réflexions double possible avec les obstacles de wall_list
    double P =0;
    
    for (int i=0; i<wall_count;i++){
        //première itération sur premier mur réflechi
        if (is_reflexion(&wall_list[i],tx,rx)){
            //Place condition sur réflexion
            Coordinates ri1 = point_image(&wall_list[i],tx);
            for (int j=0;j<wall_count;j++){
                //Seconde itération pour seconde réflexion
                if (i!=j){
                    Coordinates ri2 = point_image(&wall_list[j],&ri1);
                    Coordinates vect_d2 = diff_p(rx,&ri2);
                    IntersectionResult intersect_data_j = intersection(&wall_list[j],&vect_d2,rx);
                    //prend les données d'intersection de pr2
                    if (intersect_data_j.is_intersect){
                        
                        Coordinates vect_d1 = diff_p(&intersect_data_j.p,&ri1);
                        IntersectionResult intersect_data_i = intersection(&wall_list[i],&vect_d1,&intersect_data_j.p);
                        //prend les données d'intersection de pr1
                        if (is_reflexion(&wall_list[i],rx,&intersect_data_j.p) && intersect_data_i.is_intersect){
                            if (is_reflexion(&wall_list[j],&intersect_data_i.p,rx)){
                                double complex R1 = coef_reflexion(&wall_list[i],&vect_d1);
                                double complex R2 = coef_reflexion(&wall_list[j],&vect_d2);
                                double complex T1 = transmission(wall_list,tx,&intersect_data_i.p,wall_count);
                                double complex T2 = transmission(wall_list,&intersect_data_i.p,&intersect_data_j.p,wall_count);
                                double complex T3 = transmission(wall_list,&intersect_data_j.p,rx,wall_count);
                                double complex E = T3*T2*T1*R1*R2*csqrt(10.2)*cexp(-wall_list[0].beta*norme(vect_d2)*I)/norme(vect_d2);
                                P+= pow((cabs(E)),2);
                            }
                        }
                    }
                }
            }
            
        }
    }
    
    return P;
}