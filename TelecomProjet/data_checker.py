
from heat_map import heat_map_mb
from fonctions_de_calcul import seuil,dbm
from appart_layout import ind_rec_couloir,ind_rec_c2,ind_rec_cuisine,
from appart_layout import ind_rec_salon,ind_rec_sam,ind_rec_c1,ind_rec_sdb


def bubble_sort(array):
    """
    Algorithme de sorting des valeurs de puissance de chaque zone 
    necessaire pour la foncion try_ls, 
    renvoie la liste ranger dans l'ordre decroissant
    code un peu modifié provenant de :
    https://realpython.com/sorting-algorithms-python/#the-bubble-sort-algorithm-in-python 
    """
    n = len(array)
    for i in range(n):
        already_sorted = True
        for j in range(n - i - 1):
            if array[j][0] < array[j + 1][0]:
                array[j], array[j + 1] = array[j + 1], array[j]
                already_sorted = False
        if already_sorted:
            break
    return array


def try_ls(pow_list):
    """ Fonction permettant de scorifier les valeurs de chaque zone de lappartement en 
    fonction de la puissance totale se trouvant dans chaque piece. renvoie lindice de 
    lemplacement de lemetteur ayant la plus grande puissance dans chaque zone"""
    
    pow_couloir,pow_c2,pow_cuisine,pow_salon,pow_sam,pow_c1,pow_sdb =[],[],[],
    [],[],[],[]
    
    score =[]
    for i in range(0,len(pow_list)):
        #Ajoute la puissance pour chaque pièce de la maison dans des 
        #listes différentes
        pow_couloir.append(pow_list[i][0])
        pow_cuisine.append(pow_list[i][1])
        pow_sam.append(pow_list[i][2])
        pow_sdb.append(pow_list[i][3])
        pow_salon.append(pow_list[i][4])
        pow_c1.append(pow_list[i][5])
        pow_c2.append(pow_list[i][6])
    pow_couloir,pow_c2,pow_cuisine,pow_salon,pow_sam,pow_c1,pow_sdb =
    bubble_sort(pow_couloir),bubble_sort(pow_c2),bubble_sort(pow_cuisine),
    bubble_sort(pow_salon),bubble_sort(pow_sam),
    bubble_sort(pow_c1),bubble_sort(pow_sdb)    
    #classe les listes par valeurs de puissances dans l'ordre décroissant 
    for i in range(0,len(pow_couloir)):
        #effectue le score en fonction de l'indice des listes 
        tot=i
        for k in range(0,len(pow_c2)):
            if pow_couloir[i][1] ==pow_c2[k][1]:
                tot +=k
            elif pow_couloir[i][1] ==pow_cuisine[k][1]:
                tot +=k
            elif pow_couloir[i][1] ==pow_salon[k][1]:
                tot +=k
            elif pow_couloir[i][1] ==pow_sam[k][1]:
                tot +=k
            elif pow_couloir[i][1] ==pow_c1[k][1]:
                tot +=k
            elif pow_couloir[i][1] ==pow_sdb[k][1]:
                tot +=k
        
        score.append([tot,pow_couloir[i][1]])
    rep = score[0]
    for i in range(1,len(score)):
        if rep[0]> score[i][0]:
            rep = score[i]
            
    return rep

    




def opt_empl_1_tx(tx_list):
    """
    Calcul la repartition de puissance dans lappartement pour differents 
    emplacement demetteur  
    et définit les puissances dans chaque pièce,
    en comparant la repartition dans chaque piece grace a la fonction
    try_ls. Renvoie la repartition la plus optimale de lappartement.
    """
    pow_list =[]
    for i in range(0,len(tx_list)):
        pow_couloir,pow_c2,pow_cuisine,pow_salon,pow_sam,pow_c1,pow_sdb =0,0,0,0,0,0,0
        c_tx =heat_map_mb(tx_list[i]) # envoyez valeurs de puissances en mW,
        #donc changer 
        #retour de la fonction dans heatmap.py
        for j in range(16):
            for k in range(30):
                #prend les valeurs des puissances en fonction des 
                #différents indices 
                #de récepteur qui sont rangés en fonction de la pièce
                if j*30 +k in ind_rec_couloir:
                    pow_couloir +=c_tx[j][k]
                elif j*30 +k in ind_rec_c2:
                    pow_c2 +=c_tx[j][k]
                elif j*30 +k in ind_rec_c1:
                    pow_c1 +=c_tx[j][k]
                elif j*30 +k in ind_rec_cuisine:
                    pow_cuisine +=c_tx[j][k]
                elif j*30 +k in ind_rec_salon:
                    pow_salon +=c_tx[j][k]
                elif j*30 +k in ind_rec_sam:
                    pow_sam +=c_tx[j][k]
                elif j*30 +k in ind_rec_sdb:
                    pow_sdb +=c_tx[j][k]
        pow_list.append([[pow_couloir,i],[pow_cuisine,i],[pow_sam,i],[pow_sdb,i]
        ,[pow_salon,i],[pow_c1,i],[pow_c2,i]])
    rep = try_ls(pow_list)
    opt_tx =heat_map_mb(tx_list[rep[1]])
    for j in range(16):
        for k in range(30):
            opt_tx[j][k] = seuil(dbm(opt_tx[j][k]))
    return opt_tx,rep[1]

def opt_empl_2_tx(tx_list):
    """
    Calcul la repartition de puissance dans lappartement 
    pour differents emplacements 
    d'un couple d'emetteur en comparant la repartition dans 
    chaque piece grace a la fonction
    try_ls. Renvoie la repartition la plus optimale de lappartement.
    """
    
    pow_list =[]
    for p in range(0,len(tx_list)):
        #Ajout d'une boucle qui sert à prendre une paire d'émetteur
        pow_couloir,pow_c2,pow_cuisine,pow_salon,pow_sam,pow_c1,pow_sdb =0,0,0,0,0,0,0
        
        c_tx =heat_map_mb(tx_list[p])
        for j in range(16):
            for k in range(30):
                if j*30 +k in ind_rec_couloir:
                    pow_couloir +=c_tx[j][k]
                elif j*30 +k in ind_rec_c2:
                    pow_c2 +=c_tx[j][k]
                elif j*30 +k in ind_rec_c1:
                    pow_c1 +=c_tx[j][k]
                elif j*30 +k in ind_rec_cuisine:
                    pow_cuisine +=c_tx[j][k]
                elif j*30 +k in ind_rec_salon:
                    pow_salon +=c_tx[j][k]
                elif j*30 +k in ind_rec_sam:
                    pow_sam +=c_tx[j][k]
                elif j*30 +k in ind_rec_sdb:
                    pow_sdb +=c_tx[j][k]
        for i in range(0,len(tx_list)):
            pow_couloirb,pow_c2b,pow_cuisineb,pow_salonb,pow_samb,pow_c1b,pow_sdbb =
            pow_couloir,pow_c2,pow_cuisine,pow_salon,pow_sam,pow_c1,pow_sdb
            c_tx =heat_map_mb(tx_list[i])
            for j in range(16):
                for k in range(30):
                    if j*30 +k in ind_rec_couloir:
                        pow_couloirb +=c_tx[j][k]
                    elif j*30 +k in ind_rec_c2:
                        pow_c2b +=c_tx[j][k]
                    elif j*30 +k in ind_rec_c1:
                        pow_c1b +=c_tx[j][k]
                    elif j*30 +k in ind_rec_cuisine:
                        pow_cuisineb +=c_tx[j][k]
                    elif j*30 +k in ind_rec_salon:
                        pow_salonb +=c_tx[j][k]
                    elif j*30 +k in ind_rec_sam:
                        pow_samb +=c_tx[j][k]
                    elif j*30 +k in ind_rec_sdb:
                        pow_sdbb +=c_tx[j][k]
        pow_list.append([[pow_couloirb,i,p],[pow_cuisineb,i,p],[pow_samb,i,p],[pow_sdbb,i,p],
        [pow_salonb,i,p],[pow_c1b,i,p],[pow_c2b,i,p]])
    rep = try_ls(pow_list)
    
    opt_tx =heat_map_mb(tx_list[rep[1]])
    opt_tx2 =heat_map_mb(tx_list[rep[2]])
    for j in range(16):
        for k in range(30):
            opt_tx[j][k] = seuil(dbm(max(opt_tx[j][k],opt_tx2[j][k])))
    
    return opt_tx,rep[1],rep[2]

