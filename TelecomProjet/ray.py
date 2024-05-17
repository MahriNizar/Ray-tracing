import matplotlib.pyplot as plt
from matplotlib import cm, colors


def ray_tracing(coo,P_dbm):
    """
    fonction permettant de tracer les rayons, prend les valeurs de coordonnées et de puissanc et les trace
    """
    cmap = plt.get_cmap('viridis')
    norm = colors.Normalize(-110,-30) 
    scalar_map = plt.cm.ScalarMappable(norm=norm, cmap=cmap)  # Création de la colorbar
    scalar_map.set_array([])    
    for i in range(1,len(coo)):
        plt.plot((coo[i-1].x,coo[i].x),(coo[i-1].y,coo[i].y),color=scalar_map.to_rgba(P_dbm))


