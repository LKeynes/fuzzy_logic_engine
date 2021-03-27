from pyfuzzylib.aggregation import *
from pyfuzzylib.defuzzification import *
from pyfuzzylib.rules import *
from pyfuzzylib.variables import *

class FuzzyEngine(object):
    """This class defines the inferential engine with fuzzy logic.
    This contains: input variables, consequent variables, rules to apply to have the inference, defuzzification method and aggregation method to use.
    """
    def __init__(self, name=None, description=None, variables=None, rules=None, aggregation_method = None, defuzzification_method = None):
        """
        Can be initialized without parameters and an empty engine will be created
        
        Keyword Arguments:
        
        name -- a name for the new Engine
        description -- a short description of what this Engine will do
        variables -- a dictionary of FyzztVariables() with variable names as keys
        rules -- a list of FuzzyRules() objects
        aggregation_method -- an AggregateMethod() subclass
        defuzzification_method -- a DefuzzyMethod() subclass
        
        If no arguments, an empty engine will be created
        """
        if name:
            self.name = name
        else:
            self.name = "Unnamed"
            
        if description:
            self.description = description
        else:
            self.description = ""
        
        if variables:
            self.variables = variables
        else:
            self.variables = {}
        
        if rules:
            self.rules = rules
        else:
            self.rules = []
            
        if aggregation_method:
            self.aggregation_method = aggregation_method
        else:
            self.aggregation_method = AggregateMin()
        
        if defuzzification_method:
            self.defuzzification_method = defuzzification_method
        else:
            self.defuzzification_method = DefuzzyCenterOfGravity()
        self.consequent_degrees = {}
        
    def setInput(self, variable, crisp):
        """
        A new input to use to run the engine:
        
        Keyword Arguments:
        
        variable -- a FuzzyVariable() object
        crisp -- a float value
        """
        self.variable_crisp[variable.name] = crisp
    
    def addRule(self, aFuzzyRule):
        """
        Add a rule to the rules list:
        
        Keyword Arguments:
        
        aFuzzyRule -- a FuzzyRule() object
        """
        self.rules.append(aFuzzyRule)
        self.rules.sort()
    
    def inputList(self):
        """
        this method returns a list of variable names that are inputs of the engine according to added rules
        """
        #this returns a list of variable names that are inputs of the engine according to the rules
        consList = set([x.consequent.variable.name for x in self.rules])
        #input are variables consequents of no rules
        return [x for x in self.variables.keys() if x not in consList]
    
    def run(self, inputs = {}):
        """
        Run the engine and get its output:
        
        Keyword Arguments:
        
        inputs -- a dictionary containing crisp values associated to variable names (keys of the dictionary)
        """
        self.rules.sort()
        """
        required_inputs = self.inputList()
        missing = [x for x in required_inputs if x not in inputs.keys()]
        if len(missing) > 0:
            raise Exception("missing inputs:\n{0}".format("\n".join(missing)))
            return
        """
        self.variable_crisp = inputs
        for k in self.variable_crisp:
            self.variable_crisp[k] = float(self.variable_crisp[k])
        n_rules = len(self.rules)
        i = 0
        #per ogni regola
        for i in range(n_rules):
            #applico la regola che va a riempirmi il dizionario consequent_degrees
            self.runRule(i)
            #per ogni elemento inserito in consequent_degrees
            for k in self.consequent_degrees.keys():
                #lo inserisco defuzzificato nel dizionario variable_crisp che usero' poi per le regole successive
                self.variable_crisp[k] = self.defuzzification_method(self.variables[k], self.consequent_degrees[k])
        #finite le regole, in consequent_degrees avro' tutti i risultati che salvo nel dizionario out
        out = self.consequent_degrees
        for k in out.keys():
            #ogni elemento del dizionario di output lo defuzzifico per trovare il valore crisp
            out[k] = self.defuzzification_method(self.variables[k], out[k])
        #a questo punto posso azzerare il dizionario dei conseguenti per il prossimo run
        self.consequent_degrees = {} 
        return out
    
    def runRule(self, rule):
        # apply the rule and get a degree of truth for the consequent
        r = self.rules[rule]
        antecs = [a for a in r.antecedents.keys()]
        if not len(antecs) == len([a for a in antecs if a in self.variable_crisp.keys()]):
            print "la regola {0} non puo' essere eseguita".format(rule)
            return
        for k in r.antecedents.keys():
            if k not in self.variable_crisp.keys():
                try:
                    self.variable_crisp[k] = self.defuzzification_method(self.variables[k],consequent_degrees[k])
                except:
                    raise Exception("Error: {0} input value is missing".format(k))
                    return False
        antecedent_degrees = r.applyRule(self.variable_crisp)
        consequent_degree = self.calculate_consequent_degree(antecedent_degrees)
        
        
        if not self.consequent_degrees.has_key(self.rules[rule].consequent.variable.name):
            self.consequent_degrees[self.rules[rule].consequent.variable.name] = {}
            
        if not self.consequent_degrees[self.rules[rule].consequent.variable.name].has_key(self.rules[rule].consequent.fuzzyset):
            self.consequent_degrees[self.rules[rule].consequent.variable.name][self.rules[rule].consequent.fuzzyset] = []
        self.consequent_degrees[self.rules[rule].consequent.variable.name][self.rules[rule].consequent.fuzzyset].append(consequent_degree)
        
            

    def calculate_consequent_degree(self, degreesVector):
        return self.aggregation_method(degreesVector)
    
    def __str__(self):
        string = "Aggregation method:\n%s" % (self.aggregation_method)
        string += "\n\nDefuzzify method:\n%s" % (self.defuzzification_method)
        string += "VARIABLES:"
        for v in self.variables.keys():
            string += "\n\n%s" % (self.variables[v])
        string += "\n\n\nRULES:"
        for r in self.rules:
            string += "\n%s" % (r)
            
        return string
        
    def getDict(self):
        """
        get a dictionary which describes the whole engine
        """
        d = {
            'name': self.name,
            'description': self.description,
            'variables':{},
            'rules':[],
            'aggregation_method':self.aggregation_method.getType(),
            'defuzzification_method':self.defuzzification_method.getType()
        }
        
        for v in self.variables.keys():
            var = self.variables[v].getDict()
            d['variables'][v]=var
        for r in self.rules:
            d['rules'].append(r.getDict())
        return d
        
    def export_to_string(self):
        """
        Get a string with the result of getDict method
        """
        return str(self.getDict())
        
    def import_from_string(self, string):
        """
        Generate the whole engine (variables, rules, etc...) from a string get by export_to_string method
        
        Keyword Arguments:
        
        string -- the string obtained by export_to_string()
        """
        self.variables = {}
        self.rules = []
        d=eval(string)
        self.aggregation_method = eval(d['aggregation_method'])
        self.defuzzification_method = eval(d['defuzzification_method'])
        self.name = d['name']
        self.description = d['description']
        for v in d['variables'].keys():
            self.variables[v] = FuzzyVariable(v)
            for fs in d['variables'][v]['fuzzy_sets'].keys():
                self.variables[v].addFuzzyset(fs,d['variables'][v]['fuzzy_sets'][fs])
        for r in d['rules']:
            newrule = FuzzyRule()
            cons = self.variables[r['consequent'][0]]
            consequent_fs = r['consequent'][1]
            for ant in r['antecedents']:
                var = self.variables[ant[0]]
                oper = ant[1]
                fs = ant[2]
                newrule.addAntecedent(var,fs,oper)
            newrule.setConsequent(cons,consequent_fs)
            self.rules.append(newrule)
                
