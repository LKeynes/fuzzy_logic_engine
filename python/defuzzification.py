class DefuzzyMethod(object):
    """
    define the method to use to find the crisp value of a variable, giving the degrees of its fuzzysets
    """
    def __init__(self):
        pass
        
    def getType(self):
        """
        this method should be implemented in subclasses and must return the name of the class,
        
        example: return "DefuzzyMethod()"
        """
        pass

    def __call__(self, variable, degrees):
        # implemented in subclasses
        # degrees is a dictionary that has fuzzyset names as keys and arrays of degrees as elements
        pass

    def __str__(self):
        t = str(type(self))
        return "{0}: {1}".format(t.replace("<class 'pyfuzzylib.defuzzification.","").replace("'>",""), self.description)

class DefuzzyCenterOfGravity(DefuzzyMethod):
    """This method uses center of gravity to define a crisp value for the fuzzy variable"""
    def __init__(self):
        self.description = "Uses center of gravity to define a crisp value for the fuzzy variable"
        self.type = "CENTER OF GRAVITY"
    
    def getType(self):
        return "DefuzzyCenterOfGravity()"

    def __call__(self, variable, degrees):
        centers = []
        for fuzzyset in degrees.keys():
            for degree in degrees[fuzzyset]:
                if degree > 0:
                    center_of_gravity = variable.fuzzy_sets[fuzzyset].center_of_gravity(degree)
                    area = variable.fuzzy_sets[fuzzyset].area(degree)
                    centers.append((center_of_gravity, area))
        weighted_sum_of_centers = sum([x[0]*x[1] for x in centers])
        weights_sum = sum(x[1] for x in centers)
        if not weights_sum == 0:
            weighted_avarage = weighted_sum_of_centers / weights_sum
            return weighted_avarage
