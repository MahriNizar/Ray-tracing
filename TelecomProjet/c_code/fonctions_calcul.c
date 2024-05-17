#include "fonctions_calcul.h"
#define Z0 sqrt((4 * 3.14159265359 * 1e-7)/(8.8541878 * 1e-12)) 

double cos_angle_i(Wall *wall,Coordinates *d){
    //calcul le cos de l'angle i en fonction d'un mur et du vecteur incident et le renvoie
    double res;
    double norm_d = norme_p(d);
    res = fabs(((d->x)/norm_d)* wall->unit_normal.x + ((d->y)/norm_d)*wall->unit_normal.y);
    
    return res;

}

double sin_angle_i(Wall *wall,Coordinates *d){
    //calcul le sin de l'angle i en fonction en appelant la fonction cos
    double res;
    res = sqrt(1-pow(cos_angle_i(wall,d),2));
    return res;
}

double sin_angle_t(Wall *wall,Coordinates *d){
    //calcul le sin de l'angle t en fonction de la permittivité du mur et de la fonction sin_angle_i
    double res;
    res = sqrt(1/wall->rel_perm)*sin_angle_i(wall,d);
    return res;
}


double cos_angle_t(Wall *wall,Coordinates *d){
    //calcul le cos de l'angle t en appelant la fonction sin_angle_t
    double res;
    res = sqrt(1-pow(sin_angle_t(wall,d),2));
    return res;
}

double propag_mur(Wall *wall,Coordinates *d){
    // calcul la distane parcourure dans le mur à l'aide de la fonction cos_angle_t
    return (wall->width/cos_angle_t(wall,d));
}

char is_reflexion(Wall *wall,Coordinates *tx,Coordinates *rx ){
    //vérifie si entre un point émetteur ou réflectif si il y a possibilité d'arriver sur un point récepteur 
    // se réfléchissant sur un mur.
    Coordinates sn = diff_p(tx,&wall->pos_debut);
    Coordinates orx = diff_p(rx,&wall->pos_debut);
    if ((prod_scal(wall->unit_normal,sn)*prod_scal(wall->unit_normal,orx))>0){
        return 1;
    }
    return 0;

}

Coordinates point_image(Wall *wall,Coordinates *tx){
    //calcul le point image d'un mur et d'un point émetteur
    double scal_val = 2*prod_scal(diff_p(tx,&wall->pos_debut),wall->unit_normal);
    
    Coordinates ri = diff_p1(tx,scal_p(&wall->unit_normal,scal_val));
    
    return ri;
}

double complex coef_reflexion(Wall *wall,Coordinates *d){
    //calcul le coefficient de reflexion 
    double complex res;
    double complex ref_perp = coeff_reflexion_perp(wall,d);
    double s = propag_mur(wall,d);
    double sint = sin_angle_t(wall,d);
    double sini = sin_angle_i(wall,d);
    double complex num = (1-cpow(ref_perp,2))*(ref_perp*cexp(-2*wall->gamma*s)*cexp(wall->beta*2*s*sint*sini*I));
    
    double complex den = (1-cpow(ref_perp,2)*(cexp(-2*wall->gamma*s)*cexp(wall->beta*2*s*sint*sini*I)));
    
    res = ref_perp - num/den ;
    return res;

}

double complex coeff_reflexion_perp(Wall *wall,Coordinates *d){
    //calcul le coefficient de reflexion perpendiculaire
    double complex Zm = wall->impedance;
    double cosi =cos_angle_i(wall,d);
    double cost = cos_angle_t(wall,d);
    double complex coef_ref_p = (Zm*cosi -Z0*cost)/(Zm*cosi +Z0*cost);
    return coef_ref_p;
}

double complex coef_transmission(Wall *wall,Coordinates *d){
    //calcul le coefficient de transmission
    double complex ref_perp = cpow(coeff_reflexion_perp(wall,d),2);
    double s = propag_mur(wall,d);
    double complex num = (1-ref_perp)*cexp(-wall->gamma*s);
    double complex den = 1-ref_perp*cexp(-2*wall->gamma*s)*cexp(I*wall->beta*2*s*sin_angle_t(wall,d)*sin_angle_i(wall,d));
    return num/den;
}
double complex transmission(Wall *wall_list,Coordinates *tx,Coordinates *rx,int wall_count){
    //vérifie si il y a un passage au travers d'un obstacle et fait appel au calcul de transmission pour en 
    //calculer la valeur
    Coordinates d = diff_p(rx,tx);
    double complex T = 1+0*I;
    for (int i =0;i<wall_count;i++){
        // fait appel a la structure intersectionResult pour en tirer les informations d'intersection
        IntersectionResult intersect_data = intersection(&wall_list[i],&d,tx);
        if( (intersect_data.is_intersect) && (fmin(tx->x,rx->x)<= intersect_data.p.x && intersect_data.p.x<=fmax(tx->x,rx->x)) 
        && (fmin(tx->y,rx->y)<= intersect_data.p.y && intersect_data.p.y<=fmax(tx->y,rx->y))) {
            // regarde si il y a intersection et si l'intersection se fait bien dans les dimensions du murs
            if (distance_p(tx,intersect_data.p)>0.001 && distance_p(rx,intersect_data.p)>0.001){
                //prend en compte seulement les valeurs voulues
                T *=coef_transmission(&wall_list[i],&d);
                
                

            }
            
        }
    }
    return T;
}

