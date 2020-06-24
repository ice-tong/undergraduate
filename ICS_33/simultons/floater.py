# A Floater is Prey; it updates by moving mostly in
#   a straight line, but with random changes to its
#   angle and speed, and displays as ufo.gif (whose
#   dimensions (width and height) are computed by
#   calling .width()/.height() on the PhotoImage


from prey import Prey
from random import random


class Floater(Prey):
    
    radius = 5
    
    def __init__(self,x,y): 
        Prey.__init__(self,x,y,2*Floater.radius,2*Floater.radius,0,5)
        self.randomize_angle()
        
    def update(self):
        if random() < 0.30:
            curr_angle = self.get_angle()
            self.set_angle(curr_angle + (random()-0.5))
            
            curr_speed = self.get_speed()
            if curr_speed < 3.5:
                self.set_speed(curr_speed + 
                               ( random()*(-2.5+curr_speed) - (curr_speed-3) ))
                
            elif curr_speed > 6.5:
                self.set_speed(curr_speed + 
                               ( random()*(7.5-curr_speed) - 0.5 ))
            
            else:
                self.set_speed(curr_speed + (random()-0.5))
                
        self.move()
            
    def display(self, the_canvas):
        x,y = self.get_location()
        the_canvas.create_oval(x-Floater.radius,y-Floater.radius,
                               x+Floater.radius,y+Floater.radius, fill = 'red')
        
        