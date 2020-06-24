'''
The Special class inherits from both Black_Hole and Mobile_Simulton.
A Special object acts as a speed version of a Hunter
with the same Prey-finding characteristics.
A Special object has the same counting mechanism like a Hunter,
but when Special eats Prey, its speed is increased by 1 pixel/update.
If it goes 30 cycles without eating Prey, speed decreases by 1 pixel/update.
For balance, Special can only reach a max speed of 15 pixels/update.
If its speed is reduced to 0, it removes itself from the simulation.
Initial velocity = 5 pixels per update @ randomized angle
Range of view = 100 pixels
'''

from blackhole import Black_Hole
from mobilesimulton import Mobile_Simulton
from prey import Prey
from math import atan2

class Special(Black_Hole, Mobile_Simulton):
    
    counter = 30
    killzone = 100
    max_speed = 15
    
    def __init__(self, x, y):
        Black_Hole.__init__(self,x,y)
        Mobile_Simulton.__init__(self,x,y,*self.get_dimension(),0,5)
        self.randomize_angle()
        self.count = 0
        
    def update(self, model):
        targets = model.find(lambda s: isinstance(s, Prey)
                           and self.distance(s.get_location()) <= Special.killzone)
        if len(targets) > 0:
            target = sorted([t for t in targets],
                            key = lambda t: self.distance(t.get_location()))[0]
            x,y = self.get_location()
            tx, ty = target.get_location()
            self.set_angle(atan2(ty-y, tx-x))
            
        self.move()
        
        eaten = Black_Hole.update(self, model)
        if len(eaten) > 0:
            self.count = 1
            if self.get_speed() <= Special.max_speed:
                self.set_speed(self.get_speed() + len(eaten))
            if self.get_speed() > Special.max_speed:
                self.set_speed(Special.max_speed)
        else:
            if self.count == Special.counter:
                self.set_speed(self.get_speed() - 1)
                if self.get_speed() == 0:
                    model.to_be_removed.add(self)
                self.count = 1
            else:
                self.count += 1
        
        return eaten