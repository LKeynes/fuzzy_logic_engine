import random
import time

class AggregateMethod(object):
    """
    This class defines a method to use to calculate the degree of consequent, according to degrees of input variables
    """
    def __init__(self):
        pass
    
    def getType(self):
        """
        this method should be implemented in subclasses and must return the name of the class,
        
        example: return "AggregateMethod()"
        """
        pass

    def __call__(self, vector):
        """
        every subclass should implement this function that must return a float between 0 and 1: degree of consequent
        
        vector has to contain float values between 0 and 1
        """
        pass

    def __str__(self):
        t = str(type(self))
        return "{0}: {1}".format(t.replace("<class 'pyfuzzylib.aggregation.","").replace("'>",""), self.description)


class AggregateMin(AggregateMethod):
    """
    Set Degree of consequent as the minimum between the degrees of truth of antecedents
    """
    def getType(self):
        return "AggregateMin()"
    
    def __init__(self):
        self.description = "Set Degree of consequent as the minimum between the degrees of truth of antecedents"

    def __call__(self, vector):
        return float(min(vector))

class AggregateMax(AggregateMethod):
    """
    Set Degree of consequent as the maximum between the degrees of truth of antecedents
    """
    def getType(self):
        return "AggregateMax()"
    
    def __init__(self):
        self.description = "Set Degree of consequent as the maximum between the degrees of truth of antecedents"

    def __call__(self, vector):
        return max(vector)

class AggregateAvarage(AggregateMethod):
    """
    Set Degree of consequent as the avarage of the degrees of truth of antecedents
    """
    def getType(self):
        return "AggregateAvarage()"
    
    def __init__(self):
        self.description = "Set Degree of consequent as the avarage of the degrees of truth of antecedents"

    def __call__(self, vector):
        return sum(vector)/len(vector)

class AggregateRandom(AggregateMethod):
    """
    Set Degree of consequent using one of the values in the vector
    """
    def getType(self):
        return "AggregateRandom()"
    
    def __init__(self):
        self.description = "Set Degree of consequent using one of the values in the vector"

    def __call__(self, vector):
        random.seed(time.time())
        return random.choice(vector)
