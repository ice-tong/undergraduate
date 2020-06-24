# Hunter is derived from the Mobile_Simulton/Pulsator classes: it updates
#   like a Pulsator, but it also moves (either in a straight line
#   or in pursuit of Prey), and displays as a Pulsator.


from prey import Prey
from pulsator import Pulsator
from mobilesimulton import Mobile_Simulton
from math import atan2


class Hunter(Pulsator,Mobile_Simulton):
    
    killzone = 200
    
    def __init__(self, x, y):
        Pulsator.__init__(self,x,y)
        Mobile_Simulton.__init__(self,x,y,*self.get_dimension(),0,5)
        self.randomize_angle()
        
    def update(self, model):
        targets = model.find(lambda s: isinstance(s, Prey)
                           and self.distance(s.get_location()) <= Hunter.killzone)
        if len(targets) > 0:
            target = sorted([t for t in targets],
                            key = lambda t: self.distance(t.get_location()))[0]
            x,y = self.get_location()
            tx, ty = target.get_location()
            self.set_angle(atan2(ty-y, tx-x))
            
        self.move()
        
        return Pulsator.update(self, model)
