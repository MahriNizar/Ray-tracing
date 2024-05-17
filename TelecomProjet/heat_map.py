import matplotlib.pyplot as plt
from matplotlib import cm, colors
from fonctions_de_calcul import dbm,seuil,debit
import ctypes
from concurrent.futures import ThreadPoolExecutor
from appart_layout import recepteur_list


def heat_map_mb(tx):
    """
    Prend en entrée une position de récepteur et calcule sous forme de liste les valeurs 
    de puissance sur chaque zone de 0.5x0.5 de l'appartement.
    Multi-Threading utilisé pour calculer plusieurs zone en même temps.
    Fonctions nécessaires aux calculs importé par la Shared library compiler du code C.
    Pour plusieurs émetteurs ajouter liste d'émetteur en entrée et ajouter boucle itérant sur ces valeurs
    dans la fonction calcul_puissance().
    Possible d'en retirer la heatmap pour le débit en ajoutant la fonction debit()

    """
    power_values = [[0 for _ in range(30)] for _ in range(16)]
    clibrary = ctypes.CDLL("c_code/main.so",winmode=0) 
    main = clibrary.main
    main.argtypes = [ctypes.c_double,ctypes.c_double,ctypes.c_double,ctypes.c_double] 
    main.restype =ctypes.c_double
    def calcul_puissance(rx,ry):

        P_tot = (0.0159*0.0159 / (8 * 73)) * (main(rx,ry,tx.x,tx.y))
        P_tot_dbm = debit(seuil(dbm(P_tot)))
        return P_tot_dbm

    with ThreadPoolExecutor() as executor:
        futures = [executor.submit(calcul_puissance, recepteur_list[ i * 30 + j].x,recepteur_list[ i * 30 + j].y) for i in range(16) for j in range(30)]

    for i in range(16):
        for j in range(30):
            index = i * 30 + j
            power_values[i][j] = futures[index].result()

    return power_values


