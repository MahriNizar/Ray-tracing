class Coordinates:
    """ 
    Classe permettant d'initialiser des attributs représentant les coordonnées des récepteur et émetteur, facilite l'interaction avec leur positions.
    """
    def __init__(self,x,y):
        self.x =x
        self.y= y
    def __str__(self):
        return f"({self.x}, {self.y})"
