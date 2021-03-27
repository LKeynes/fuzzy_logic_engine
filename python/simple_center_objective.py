"""
this is a simple example with just 2 variables and 2 fuzzysets per variable.
"""

from pyfuzzylib.engine import *
from random import choice
from time import sleep
from sys import stdout

engine = FuzzyEngine("Example","Simple example to show how to use this library")

engine.variables['objective'] = FuzzyVariable("objective")
engine.variables['objective'].addFuzzyset("right",[0, 1000, 1000])
engine.variables['objective'].addFuzzyset("center",[-1000,0,1000])
engine.variables['objective'].addFuzzyset("left",[-1000,-1000,0])

engine.variables['steer'] = FuzzyVariable("steer")
engine.variables['steer'].addFuzzyset("right",[-400, 1000, 1000])
engine.variables['steer'].addFuzzyset("center",[-500,0,500])
engine.variables['steer'].addFuzzyset("left",[-1000,-1000,400])

r = FuzzyRule()
r.addAntecedent(engine.variables['objective'], "right")
r.setConsequent(engine.variables['steer'], "right")
engine.addRule(r)

r = FuzzyRule()
r.addAntecedent(engine.variables['objective'], "left")
r.setConsequent(engine.variables['steer'], "left")
engine.addRule(r)

r = FuzzyRule()
r.addAntecedent(engine.variables['objective'],"center")
r.setConsequent(engine.variables['steer'], "center")
engine.addRule(r)

obj_pos = float(choice(range(-1000,1001)))
position = float(choice(range(-1000,1001)))
steps = []
start_position = position
counter = 0
rel_position = obj_pos - position
steps.append({'position':position,'relative position':rel_position})
while abs(rel_position)>0.001:
    #print "continuo"
    print "{0} non e' {1}".format(float(position), float(obj_pos))
    counter += 1
    rel_position = obj_pos - position
    inputs={'objective':rel_position}
    out = engine.run(inputs)
    position += float(out['steer'])
    rel_position = obj_pos - position
    steps.append({'position':position,'relative position':rel_position})
    #sleep(0.5)
    print "posizione relativa: {0}".format(rel_position)

print "obiettivo raggiunto in {0} tentativi:\nObiettivo in posizione {1}, partenza in {2}".format(counter,obj_pos,start_position)
print "passi:\nposizione\tobiettivo rispetto alla posizione"
for s in steps:
    print "{0:11.8}\t{1:.08}".format(s['position'],s['relative position'])
