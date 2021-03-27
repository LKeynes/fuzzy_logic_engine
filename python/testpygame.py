#!/bin/python

"""
QUESTO ESEMPIO RICHIEDE IL MODULO DI PYTHON "pygame"
"""
import pygame, sys
from pyfuzzylib.engine import *
from time import sleep

pygame.init() #load pygame modules
size = width, height = 640, 480 #size of window
target_x,target_y = width/2, height/2
s = pygame.display.set_mode(size) #make window
col = (255,255,255)
closed = False
black = [  0,  0,  0]
white = [255,255,255]
green=[0,255,0]
red = [255,0,0]
raggio = 50
screen=pygame.display.set_mode(size)

clock=pygame.time.Clock() #make a clock

def draw_target(x,y):
    screen.fill(white)
    width = size[0]
    height = size[1]
    box_dimensions = [x-raggio,y-raggio, raggio*2, raggio*2]
    pygame.draw.ellipse(screen,red,box_dimensions,2)
    pygame.display.flip() #update the screen


engine = FuzzyEngine()
engine.variables['orizzontale']=FuzzyVariable('orizzontale')
engine.variables['orizzontale'].addFuzzyset('dx',[-width/4,width,width])
engine.variables['orizzontale'].addFuzzyset('sn',[-width,-width,width/4])

engine.variables['verticale']=FuzzyVariable('verticale')
engine.variables['verticale'].addFuzzyset('su',[-height,-height,height/4])
engine.variables['verticale'].addFuzzyset('giu',[-height/4,height,height])

max_spostamento = 10

engine.variables['move_x']=FuzzyVariable('move_x')
engine.variables['move_x'].addFuzzyset('dx',[-max_spostamento/4,max_spostamento,max_spostamento])
engine.variables['move_x'].addFuzzyset('sn',[-max_spostamento,-max_spostamento,max_spostamento/4])

engine.variables['move_y']=FuzzyVariable('move_y')
engine.variables['move_y'].addFuzzyset('su',[-max_spostamento,-max_spostamento,max_spostamento/4])
engine.variables['move_y'].addFuzzyset('giu',[-max_spostamento/4,max_spostamento,max_spostamento])


r = FuzzyRule()
r.addAntecedent(engine.variables['orizzontale'],"sn")
r.setConsequent(engine.variables['move_x'], "sn")
engine.addRule(r)

r = FuzzyRule()
r.addAntecedent(engine.variables['orizzontale'],"dx")
r.setConsequent(engine.variables['move_x'], "dx")
engine.addRule(r)

r = FuzzyRule()
r.addAntecedent(engine.variables['verticale'],"su")
r.setConsequent(engine.variables['move_y'], "su")
engine.addRule(r)

r = FuzzyRule()
r.addAntecedent(engine.variables['verticale'],"giu")
r.setConsequent(engine.variables['move_y'], "giu")
engine.addRule(r)


running = True
while running:
    
    #pos = []
    for event in pygame.event.get():
        if event.type == 12 or event.type == 6:
            running = False
    # ridisegna
    draw_target(target_x,target_y)
    # mouse_pos = x_mouse,y_mouse = ...
    pos = pygame.mouse.get_pos()
    mouse_x = pos[0]
    mouse_y = pos[1]
    # objective_pos = x_obj, y_obj = (x_obj - x_mouse),(y_obj - y_mouse)
    delta_x,delta_y = mouse_x-target_x, mouse_y-target_y
    # run fuzzyengine per avere lo spostamento da effettuare in questo ciclo per raggiungere l'obiettivo
    inputs= {'orizzontale':delta_x,'verticale':delta_y}
    #print inputs
    out = engine.run(inputs)
    move_x = out['move_x']
    move_y = out['move_y']
    target_x = int(round(target_x + move_x))
    target_y = int(round(target_y + move_y))
    #print "mouse: {0}, target: {1}".format(pos,(target_x,target_y))
    sleep(0.01)
pygame.display.quit()
