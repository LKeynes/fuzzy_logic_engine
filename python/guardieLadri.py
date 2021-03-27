#!/bin/python

"""
QUESTO ESEMPIO RICHIEDE IL MODULO DI PYTHON "pygame"
"""
import pygame, sys
from pyfuzzylib.engine import *
from time import sleep,time
import random

pygame.init() #load pygame modules
size = width, height = 800, 600 #size of window
guardia_x,guardia_y = width/2, height/2
s = pygame.display.set_mode(size) #make window
col = (255,255,255)
closed = False
black = [  0,  0,  0]
white = [255,255,255]
green=[0,255,0]
red = [255,0,0]
raggio = 20
screen=pygame.display.set_mode(size)

clock=pygame.time.Clock() #make a clock

def draw_guardia(x,y):
    width = size[0]
    height = size[1]
    box_dimensions = [x-raggio,y-raggio, raggio*2, raggio*2]
    pygame.draw.ellipse(screen,green,box_dimensions,2)

def draw_ladro(x,y):
    width = size[0]
    height = size[1]
    box_dimensions = [x-raggio,y-raggio, raggio*2, raggio*2]
    pygame.draw.ellipse(screen,red,box_dimensions,2)


guardia = FuzzyEngine(name='guardia')
guardia.variables['orizzontale']=FuzzyVariable('orizzontale')
guardia.variables['orizzontale'].addFuzzyset('dx',[-0.1,0.1,width])
guardia.variables['orizzontale'].addFuzzyset('sn',[-width,-0.1,0.1])

guardia.variables['verticale']=FuzzyVariable('verticale')
guardia.variables['verticale'].addFuzzyset('su',[-height,-0.1,0.1])
guardia.variables['verticale'].addFuzzyset('giu',[-0.1,0.1,height])

max_spostamento = 10

guardia.variables['move_x']=FuzzyVariable('move_x')
guardia.variables['move_x'].addFuzzyset('dx',[-max_spostamento/4,max_spostamento,max_spostamento])
guardia.variables['move_x'].addFuzzyset('sn',[-max_spostamento,-max_spostamento,max_spostamento/4])

guardia.variables['move_y']=FuzzyVariable('move_y')
guardia.variables['move_y'].addFuzzyset('su',[-max_spostamento,-max_spostamento,max_spostamento/4])
guardia.variables['move_y'].addFuzzyset('giu',[-max_spostamento/4,max_spostamento,max_spostamento])

# regole guardia
r = FuzzyRule()
r.addAntecedent(guardia.variables['orizzontale'],"sn")
r.setConsequent(guardia.variables['move_x'], "sn")
guardia.addRule(r)

r = FuzzyRule()
r.addAntecedent(guardia.variables['orizzontale'],"dx")
r.setConsequent(guardia.variables['move_x'], "dx")
guardia.addRule(r)

r = FuzzyRule()
r.addAntecedent(guardia.variables['verticale'],"su")
r.setConsequent(guardia.variables['move_y'], "su")
guardia.addRule(r)

r = FuzzyRule()
r.addAntecedent(guardia.variables['verticale'],"giu")
r.setConsequent(guardia.variables['move_y'], "giu")
guardia.addRule(r)

ladro = FuzzyEngine(name='ladro')
ladro.variables['orizzontale']=FuzzyVariable('orizzontale')
ladro.variables['orizzontale'].addFuzzyset('dx',[-0.1,0.1,width*2])
ladro.variables['orizzontale'].addFuzzyset('sn',[-width*2,-0.1,0.1])

ladro.variables['verticale']=FuzzyVariable('verticale')
ladro.variables['verticale'].addFuzzyset('su',[-height*2,-0.1,0.1])
ladro.variables['verticale'].addFuzzyset('giu',[-0.1,0.1,height*2])

ladro.variables['posizione_x']=FuzzyVariable('posizione_x')
ladro.variables['posizione_x'].addFuzzyset('sn',[0,0,width])
ladro.variables['posizione_x'].addFuzzyset('dx',[0,width,width])

ladro.variables['posizione_y']=FuzzyVariable('posizione_y')
ladro.variables['posizione_y'].addFuzzyset('su',[0,0,height])
ladro.variables['posizione_y'].addFuzzyset('giu',[0,height,height])

max_spostamento = 200

ladro.variables['move_x']=FuzzyVariable('move_x')
ladro.variables['move_x'].addFuzzyset('dx',[-max_spostamento/4,max_spostamento,max_spostamento])
ladro.variables['move_x'].addFuzzyset('sn',[-max_spostamento,-max_spostamento,max_spostamento/4])

ladro.variables['move_y']=FuzzyVariable('move_y')
ladro.variables['move_y'].addFuzzyset('su',[-max_spostamento,-max_spostamento,max_spostamento/4])
ladro.variables['move_y'].addFuzzyset('giu',[-max_spostamento/4,max_spostamento,max_spostamento])

# regole ladro

r = FuzzyRule()
r.addAntecedent(ladro.variables['orizzontale'],"sn")
r.setConsequent(ladro.variables['move_x'], "sn")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['orizzontale'],"dx")
r.setConsequent(ladro.variables['move_x'], "dx")
ladro.addRule(r)


r = FuzzyRule()
r.addAntecedent(ladro.variables['verticale'],"su")
r.setConsequent(ladro.variables['move_y'], "su")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['verticale'],"giu")
r.setConsequent(ladro.variables['move_y'], "giu")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['posizione_x'],"sn")
r.addAntecedent(ladro.variables['posizione_y'],"su")
r.setConsequent(ladro.variables['move_y'], "giu")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['posizione_x'],"sn")
r.addAntecedent(ladro.variables['posizione_y'],"giu")
r.setConsequent(ladro.variables['move_y'], "su")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['posizione_x'],"dx")
r.addAntecedent(ladro.variables['posizione_y'],"giu")
r.setConsequent(ladro.variables['move_y'], "su")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['posizione_x'],"dx")
r.addAntecedent(ladro.variables['posizione_y'],"su")
r.setConsequent(ladro.variables['move_y'], "giu")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['posizione_y'],"su")
r.addAntecedent(ladro.variables['posizione_x'],"dx")
r.setConsequent(ladro.variables['move_x'], "sn")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['posizione_y'],"su")
r.addAntecedent(ladro.variables['posizione_x'],"sn")
r.setConsequent(ladro.variables['move_x'], "dx")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['posizione_y'],"giu")
r.addAntecedent(ladro.variables['posizione_x'],"sn")
r.setConsequent(ladro.variables['move_x'], "dx")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['posizione_y'],"giu")
r.addAntecedent(ladro.variables['posizione_x'],"dx")
r.setConsequent(ladro.variables['move_x'], "sn")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['posizione_x'],"sn")
r.setConsequent(ladro.variables['move_x'],"dx")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['posizione_x'],"dx")
r.setConsequent(ladro.variables['move_x'],"sn")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['posizione_y'],"su")
r.setConsequent(ladro.variables['move_y'],"giu")
ladro.addRule(r)

r = FuzzyRule()
r.addAntecedent(ladro.variables['posizione_y'],"giu")
r.setConsequent(ladro.variables['move_y'],"su")
ladro.addRule(r)

guardia_x,guardia_y = random.randrange(width),random.randrange(height)
ladro_x,ladro_y = random.randrange(width),random.randrange(height)

running = True
preso = False
start = time()
while running:
    #print "time: {0} start: {1}".format(int(time()),int(start))
    
    if (int(ladro_x) > width or int(ladro_x) < 0) and (int(ladro_y) > height or int(ladro_y) < 0):
        ladro_x,ladro_y = random.randrange(width),random.randrange(height)
    
    if preso:
        print "preso in {0:4.3} secondi".format(time()-start)
        sleeptime = 2
        preso = False
        guardia_x,guardia_y = random.randrange(width),random.randrange(height)
        ladro_x,ladro_y = random.randrange(width),random.randrange(height)
        start = time()+2
    else:
        sleeptime = 0.005
        
    for event in pygame.event.get():
        if event.type == 6:
            #running = False
            guardia_x,guardia_y = random.randrange(width),random.randrange(height)
            ladro_x,ladro_y = random.randrange(width),random.randrange(height)
            sleeptime = 2
            start = time()+2
        elif event.type == 12:
            running = False
            sleeptime = 0.005
        else:
            sleeptime = 0.005
            
    # ridisegna
    screen.fill(white)
    #draw_guardia(guardia_x,guardia_y)
    draw_ladro(ladro_x,ladro_y)
    draw_guardia(guardia_x,guardia_y)
    pygame.display.flip() #update the screen

    delta_x,delta_y = ladro_x-guardia_x, ladro_y-guardia_y
    
    # run fuzzyengine per avere lo spostamento da effettuare in questo ciclo per raggiungere l'obiettivo
    inputs= {'orizzontale':delta_x,'verticale':delta_y}
    #print inputs
    
    out_guardia = guardia.run(inputs)
    move_guardia_x = out_guardia['move_x']
    move_guardia_y = out_guardia['move_y']
    guardia_x = guardia_x + move_guardia_x
    guardia_y = guardia_y + move_guardia_y
    
    inputs['posizione_x'] = ladro_x
    inputs['posizione_y'] = ladro_y
    out_ladro = ladro.run(inputs)
    move_ladro_x = out_ladro['move_x']
    move_ladro_y = out_ladro['move_y']
    ladro_x = ladro_x + move_ladro_x
    ladro_y = ladro_y + move_ladro_y
    if abs(ladro_x-guardia_x)<=raggio and abs(ladro_y-guardia_y)<=raggio:
        preso=True
    
    sleep(sleeptime)
pygame.display.quit()
