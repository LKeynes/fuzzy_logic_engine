from variables import *

class FuzzyOperator:
    IS = 'IS'
    ISNOT = 'ISNOT'

class FuzzyAntecedent(object):
    """
    Antecedent of a rule
    """
    def __init__(self, aVariable, op, fuzzyset):
        """
        IF Variable IS Adjective ...:
        
        Keyword Arguments:
        aVariable -- a FuzzyVariable to use in this antecedent
        op -- a FuzzyOperator: IS/ISNOT
        fuzzyset -- an Adjective to associate to the variable in this antecedent
        """
        self.variable = aVariable
        self.fuzzyset = fuzzyset
        self.op = op

    def degree(self, crisp):
        """
        Get the degree of truth of this antecedent according to a Crisp value
        
        Keyword Arguments:
        
        crisp -- the value to get the degree of truth of this antecedent
        """
        degree_to_return = self.variable.degree(crisp, self.fuzzyset)
        if self.op == 'ISNOT':
            degree_to_return = 1 - degree_to_return
        return degree_to_return
        
    def getDict(self):
        """
        Get the dictionary describing this antecedent
        """
        return [self.variable.name, self.op, self.fuzzyset]
        
    def __str__(self):
        return "%s %s %s" % (self.variable.name, self.op, self.fuzzyset)


class FuzzyConsequent(object):
    """
    Consequent of a rule:
    """
    def __init__(self, aVariable, fuzzyset):
        """
        ...THEN Variable = adjective
        
        Keyword Arguments:
        aVariable -- a FuzzyVariable
        fuzzyset -- a string containing the adjective
        """
        self.variable = aVariable
        self.fuzzyset = fuzzyset    #string
    
    def getDict(self):
        """
        Get the dictionary describing this consequent
        """
        return [self.variable.name,self.fuzzyset]
    
    def __str__(self):
        return "%s = %s" % (self.variable.name, self.fuzzyset)


class FuzzyRule(object):
    """
    A FuzzyRule class define a rule to be applied to have the result of the fuzzy engine
    """
    def __init__(self):
        """
        No arguments are required
        """
        self.antecedents = {}
        self.consequent_degree = 0
        self.consequent = None

    def addAntecedent(self, aVariable, fuzzyset, op = FuzzyOperator.IS):
        """
        Add an antecedent.
        
        Keyword Arguments:
        aVariable -- a FuzzyVariable
        fuzzyset -- a string with an adjective
        op -- a FuzzyOperator (IS/ISNOT)
        
        """
        self.antecedents[aVariable.name] = FuzzyAntecedent(aVariable, op, fuzzyset)

    def setConsequent(self, aVariable, fuzzyset):
        """
        Add a consequent:
        aVariable -- a FuzzyVariable
        fuzzyset -- a string with an adjective
        """
        self.consequent = FuzzyConsequent(aVariable, fuzzyset)

    def applyRule(self, inputs):
        """
        Get the output of this rule according some input values.
        
        Keyword Arguments:
        
        inputs -- a dictionary that has name of variable as key, and an int/float as value
        """
        outputs = []

        for variable in self.antecedents.keys():
            crisp = inputs[variable]
            outputs.append(float(self.antecedents[variable].degree(crisp)))
        return outputs
        
    def __gt__(self,aRule):
        if aRule.consequent.variable in self.antecedents.keys():
            return True
        else:
            return False
    
    def __lt__(self,aRule):
        if self.consequent.variable in aRule.antecedents.keys():
            return True
        else:
            return False
    
    def getDict(self):
        """
        Get a dictionary that describes this rule
        """
        try:
            cons = self.consequent.getDict()
        except:
            cons = None
        return {'antecedents':[self.antecedents[a].getDict() for a in self.antecedents.keys()],'consequent':cons}
        
    def __str__(self):
        if not self.consequent or len(self.antecedents)==0:
            return "Incomplete rule"
        else:
            return "IF {0} THEN {1}".format(" AND ".join([str(self.antecedents[ant]) for ant in self.antecedents.keys()]),self.consequent)
            
