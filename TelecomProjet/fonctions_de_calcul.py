import math

def dbm(P):# mets P en dBm
    try:
        return 10*math.log10(P/0.001)
    except:
        return -10000

def seuil(P_dbm):
    #detertmine le seuil minimal pour prend des puissances bornées
    if P_dbm <-90:
        return -90
    elif  P_dbm>-40:
        return -40
    return P_dbm
def debit(P_dbm):
    deb = 0.001*10**(0.058*P_dbm+9.9189)#relation linéaire entre le débit et la puissance
    return deb