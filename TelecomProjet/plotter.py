from appart_layout import white_wall,elev_wall,metal_wall
from appart_layout import emetteur_list,glass_wall,red_wall,
import matplotlib.pyplot as plt
from matplotlib import cm, colors
from heat_map import heat_map_mb


plt.figure()
ind=0#Indice de l'émetteur dont on veut calculer la répartition 
""" Dessine les murs sur le plot"""
for i in glass_wall:
    plt.plot([i[0][0],i[1][0]],[i[0][1],i[1][1]],color="blue")
for i in red_wall:
    plt.plot([i[0][0],i[1][0]],[i[0][1],i[1][1]],color="red")
for i in white_wall:
    plt.plot([i[0][0],i[1][0]],[i[0][1],i[1][1]],color="grey")
for i in metal_wall:
    plt.plot([i[0][0],i[1][0]],[i[0][1],i[1][1]],color="black")
for i in elev_wall:
    plt.plot([i[0][0],i[1][0]],[i[0][1],i[1][1]],color="black")

""" Prépare la heatmap et la colorbar"""
cmap = plt.get_cmap('plasma')
norm = colors.Normalize(-90,-40) 
scalar_map = plt.cm.ScalarMappable(norm=norm, cmap=cmap)  
scalar_map.set_array([])
plt.colorbar(scalar_map).set_label('Puissance (dBm)')





""" Calcul nos puissances"""
pow_val2 =heat_map_mb(emetteur_list[ind])

plt.scatter(emetteur_list[ind].x,emetteur_list[ind].y)
plt.imshow(pow_val2,cmap=cmap,norm=norm,origin ='lower',extent=[0,15,0,8])
plt.tight_layout()
plt.title('Distribution de la puissance (sans ascenseur)')
plt.xlabel('m')
plt.ylabel('m')
plt.gca().set_aspect('equal', adjustable='box')
plt.grid(False)
plt.show()


