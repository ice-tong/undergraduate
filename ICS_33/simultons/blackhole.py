# Black_Hole is derived from Simulton only: it updates by finding/removing
#   any Prey whose center is contained within its radius
#  (returning a set of all eaten simultons), and
#   displays as a black circle with a radius of 10
#   (width/height 20).
# Calling get_dimension for the width/height (for
#   containment and displaying) will facilitate
#   inheritance in Pulsator and Hunter

from simulton import Simulton
from prey import Prey


class Black_Hole(Simulton):
    
    radius = 10
    
    def __init__(self, x, y):
        Simulton.__init__(self,x,y,2*Black_Hole.radius,2*Black_Hole.radius)
        
    
    def update(self, model):
        return model.find(lambda s: self.contains(s.get_location())
                          and isinstance(s, Prey))
       

    
    def display(self, the_canvas):
        x,y = self.get_location()
        w,h = self.get_dimension()
        
        the_canvas.create_oval(x-(w/2),y-(h/2),
                               x+(w/2),y+(h/2), fill = 'black')
        
    
    def contains(self, xy):
        return self.distance(xy) < self.get_dimension()[0]/2