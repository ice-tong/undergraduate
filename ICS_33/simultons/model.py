import controller
import model   #strange, but we need a reference to this module to pass this module to update

from ball      import Ball
from floater   import Floater
from blackhole import Black_Hole
from pulsator  import Pulsator
from hunter    import Hunter
from special   import Special


# Global variables: declare them global in functions that assign to them: e.g., ... = or +=
running = False
cycles = 0
simultons = set()
selected_button = ''
to_be_removed = set()

#return a 2-tuple of the width and height of the canvas (defined in the controller)
def world():
    return (controller.the_canvas.winfo_width(),controller.the_canvas.winfo_height())

#reset all module variables to represent an empty/stopped simulation
def reset ():
    global running, cycles, simultons
    running = False
    cycles = 0
    simultons = set()


#start running the simulation
def start ():
    global running
    running = True


#stop running the simulation (freezing it)
def stop ():
    global running
    running = False


#step just one update in the simulation
def step ():
    start()
    update_all()
    stop()


#remember the kind of object to add to the simulation when an (x,y) coordinate in the canvas
#  is clicked next (or remember to remove an object by such a click)   
def select_object(kind):
    global selected_button
    selected_button = kind


#add the kind of remembered object to the simulation (or remove all objects that contain the
#  clicked (x,y) coordinate
def mouse_click(x,y):
    if selected_button != '':
        if selected_button == 'Remove':
            for s in find(lambda s: s.contains((x,y))):
                remove(s)
        else:
            add(eval(selected_button+f'({x},{y})'))


#add simulton s to the simulation
def add(s):
    simultons.add(s)
    

# remove simulton s from the simulation    
def remove(s):
    simultons.remove(s)
    

#find/return a set of simultons that each satisfy predicate p    
def find(p):
    return {s for s in simultons if p(s)}


#call update for every simulton in the simulation
def update_all():
    global cycles
    if running:
        cycles += 1
        for s in simultons:
            if type(s) in {Ball, Floater}:
                s.update()
            elif type(s) in {Black_Hole, Pulsator, Hunter, Special}:
                global to_be_removed
                to_be_removed = to_be_removed.union(s.update(model))
        for r in to_be_removed:
            remove(r)
        to_be_removed = set()       
                


#delete every simulton being simulated from the canvas; then call display for every
#  simulton being simulated to add it back to the canvas, possibly in a new location, to
#  animate it; also, update the progress label defined in the controller
def display_all():
    for s in controller.the_canvas.find_all():
        controller.the_canvas.delete(s)
    
    for s in simultons:
        s.display(controller.the_canvas)
    
    controller.the_progress.config(text=str(len(simultons))+" simultons/"+str(cycles)+" cycles")
