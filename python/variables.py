import math
class Fuzzyset(object):
    def __init__(self, values, name):
        self.name = name
        self.values = values
        pass

    def degree(self, crisp):
        """
        this function has to be developed in subclasses and returns the degree that the fuzzyset has into a crisp value
        """
        pass

    def center_of_gravity(self, degree):
        """
        this function has to be developed in subclasses and returns the crisp value that represent the center of the fuzzy set
        """
        pass
    
    def area(self, degree):
        """
        this function has to be developed in subclasses and returns the area of the fuzzyset according to a degree
        """
        pass

    def __str__(self):
        string = "%s - %s:\t" % (self.name, self.shape)
        for v in self.values:
            string += " %s\t|" % (v)
        return string
        
    def __lt__(self, aFuzzySet):
        return self.center_of_gravity(1) < aFuzzySet.center_of_gravity(1)
        
    def __le__(self, aFuzzySet):
        return self.center_of_gravity(1) <= aFuzzySet.center_of_gravity(1)
    
    def __gt__(self, aFuzzySet):
        return self.center_of_gravity(1) > aFuzzySet.center_of_gravity(1)
    
    def __ge__(self, aFuzzySet):
        return self.center_of_gravity(1) >= aFuzzySet.center_of_gravity(1)
    
    def __eq__(self, aFuzzySet):
        return (self.center_of_gravity(1) == aFuzzySet.center_of_gravity(1)) and (self.name == aFuzzySet.name)
    
    def __ne__(self, aFuzzySet):
        return (self.center_of_gravity(1) != aFuzzySet.center_of_gravity(1)) or (self.name != aFuzzySet.name)
        
    def getDict(self):
        d = {}
        vals = []
        for v in self.values:
            vals.append(v)
        d[self.name] = vals
        return d
    

class TriangularFuzzyset(Fuzzyset):
    """
    Triangular shaped Fuzzyset. It has three values: left angle, center and right ones. Left and right ones has degree 0. The center value has degree 1
    """
    def __init__(self, values, name):
        """
        Keyword Arguments:
        
        values -- a list of float values
        name -- an adjective (string) to associate to this set
        """
        self.name = name
        self.shape = "TRIANGULAR"
        if len(values) == 3:
            self.values = values
            self.values.sort()
            i = 0
            for v in self.values:
                self.values[i] = float(v)
                i=i+1

    def degree(self, crisp):
        """
        get the degree corresponding a crisp value
        
        Keyword Arguments:
        crisp -- a float value to get the degree corresponding to
        """
        c = crisp
        # crips should be between min and max
        if c < self.values[0]:
            c = self.values[0]
        elif c > self.values[2]:
            c = self.values[2]
            
        if c == self.values[1]:
            return 1
        elif c == self.values[0] or c == self.values[2]:
            return 0
        elif c > self.values[0] and c < self.values[1]:
            """
            calculate degree on the left side of the triangle
            """
            return (c - self.values[0]) / (self.values[1] - self.values[0])
        else:
            """
            calculate degree on the right side of the triangle
            """
            return abs((self.values[2] - c) / (self.values[1] - self.values[2]))

    def center_of_gravity(self, degree = 1):
        """
        Get the crisp value at the center of this set according to a certain degree
        
        Keyword Arguments:
        
        degree -- a degree to get the corresponding center of gravity. If None, the center of gravity of the whole set is returned
        """
        x1 = self.values[0] - degree * (self.values[0] - self.values[1])
        x2 = self.values[2] - degree * (self.values[2] - self.values[1])
        return (self.values[0] + x1 + x2 + self.values[2]) / 4
        
    def area(self, degree=1):
        """
        Get the area of this set according to a certain degree
        
        Keyword Arguments:
        degree -- a degree to get the corresponding Area. If None, the area of the whole set is returned
        """
        if degree == 1:
            return (self.values[2] - self.values[0]) * 0.5
        else:
            x1 = self.values[0] - degree * (self.values[0] - self.values[1])
            x2 = self.values[2] - degree * (self.values[2] - self.values[1])
            b1 = self.values[2] - self.values[0]
            b2 = x2 - x1
            return (b1 + b2) * degree * 0.5

class TrapezioidalFuzzyset(Fuzzyset):
    """
    Trapezoidal shaped Fuzzyset. It has four values:
    - first, the left point of the longer base
    - second the left point of the shorter base
    - Third the right point of the shorter base
    - Last the right point of the longer base
    """
    def __init__(self, values, name):
        """
        Keyword Arguments:
        
        values -- a list of float values
        name -- an adjective (string) to associate to this set
        """
        self.name = name
        self.shape = "TRAPEZIOIDAL"
        if len(values) == 4:
            self.values = values
            self.values.sort()
            i = 0
            for v in self.values:
                self.values[i] = float(v)
                i=i+1
    def degree(self, crisp):
        """
        get the degree corresponding a crisp value
        
        Keyword Arguments:
        crisp -- a float value to get the degree corresponding to
        """
        c = crisp
        # crips should be between min and max
        if c < self.values[0]:
            c = self.values[0]
        elif c > self.values[3]:
            c = self.values[3]
        
        if self.values[1] <= c <= self.values[2]:
            return 1
        elif c == self.values[0] or c == self.values[3]:
            return 0
        elif c < self.values[1]:
            return (c - self.values[0]) / (self.values[1] - self.values[0])
        else:
            return abs((self.values[3] - c) / (self.values[2] - self.values[3]))

    def center_of_gravity(self, degree = 1):
        """
        Get the crisp value at the center of this set according to a certain degree
        
        Keyword Arguments:
        
        degree -- a degree to get the corresponding center of gravity. If None, the center of gravity of the whole set is returned
        """
        x1 = self.values[0] - degree * (self.values[0] - self.values[1])
        x2 = self.values[3] - degree * (self.values[3] - self.values[2])
        return (self.values[0] + x1 + x2 + self.values[3]) / 4
        
    def area(self, degree=1):
        """
        Get the area of this set according to a certain degree
        
        Keyword Arguments:
        degree -- a degree to get the corresponding Area. If None, the area of the whole set is returned
        """
        if degree == 1:
            b1 = self.values[3] - self.values[0]
            b2 = self.values[2] - self.values[1]
        else:
            x1 = self.values[0] - degree * (self.values[0] - self.values[1])
            x2 = self.values[3] - degree * (self.values[3] - self.values[2])
            b1 = self.values[3] - self.values[0]
            b2 = x2 - x1
        return (b1 + b2) * degree * 0.5


class GaussianFuzzySet(Fuzzyset):
    """NOT COMPLETE"""
    def __init__(self, values, name):
        self.name = name
        self.shape = "GAUSSIAN"
        if len(values) == 2:
            self.average = values[0]
            self.variance = values[1]
    def degree(self, crisp):
        x = crisp
        return ((1/(math.sqrt(2*math.pi)*self.variance)) * math.pow(math.e, ((-1/2)* math.pow(((x-self.average)/self.variance), 2))))


class FuzzyVariable(object):
    """
    A FuzzyVariable has a name and an array of FuzzySet that defines the variable
    """
    def __init__(self, name):
        """
        just give a name to the variable to create it
        """
        self.name = name
        self.max_value = None
        self.min_value = None
        self.fuzzy_sets = {}

    def addFuzzyset(self, name, values):
        """
        to add a fuzzyset to this variable:
        
        Keyword Arguments:
        
        name -- the adjective to associate to this set
        values -- a list of int/float values. The shape varies according to the length of this list
        """
        if self.max_value is None and self.min_value is None:
            self.max_value = float(max(values))
            self.min_value = float(min(values))
        else:
            if self.max_value < max(values):
                self.max_value = float(max(values))
            if self.min_value > min(values):
                self.min_value = float(min(values))
        if len(values) == 3:
            self.fuzzy_sets[name] = TriangularFuzzyset(values, name)
        elif len(values) == 4:
            if values[1] == values[2]:
                self.fuzzy_sets[name] = TriangularFuzzyset([values[0], values[1], values[3]], name)
            else:
                self.fuzzy_sets[name] = TrapezioidalFuzzyset(values, name)
        elif len(values) == 2:
            self.fuzzy_sets[name] = GaussianFuzzyset(values, name)

    def editFuzzyset(self, name, values):
        """
        Modify a fuzzyset.
        
        Keyword Arguments:
        
        name -- the adjective to associate to this set
        values -- a list of int/float values. The shape varies according to the length of this list
        """
        if self.fuzzy_sets.has_key(name):
            if self.max_value < max(values):
                self.max_value = float(max(values))
            if self.min_value > min(values):
                self.min_value = float(min(values))
            if len(values) == 3:
                self.fuzzy_sets[name] = TriangularFuzzyset(values)
            elif len(values) == 4:
                self.fuzzy_sets[name] = TrapezioidalFuzzyset(values)
            elif len(values) == 2:
                self.fuzzy_sets[name] = GaussianFuzzyset(values)
        else:
            return False

    def degree(self, c, fuzzy_set):
        """
        Get the degree of a fuzzyset to a crisp value
        
        Keyword Arguments:
        
        c -- int/float crisp value
        fuzzy_set -- a string containing the name of the fuzzy_set to get the degree of, according to the c crisp value
        """
        crisp = float(c)
        if crisp > self.max_value:
            crisp = self.max_value
        if crisp < self.min_value:
            crisp = self.min_value
        return self.fuzzy_sets[fuzzy_set].degree(crisp)
    
    def get_fuzzysets(self):
        """
        Get the dictionary describing the fuzzysets of this variable
        """
        return sorted([self.fuzzy_sets[x].getDict for x in self.fuzzy_sets.keys() ])
            
    def get_degrees(self,c):
        """
        this method returns a dictionary with all fuzzyset degrees related to the crisp:
        
        {'fuzzyset_name':degree}
        """
        crisp = float(c)
        d = {}
        for k in self.fuzzy_sets.keys():
            d[k] = self.degree(crisp,k)
        return d

    def __str__(self):
        string = "{0}: MIN({1}) - MAX({2})".format(self.name, self.min_value, self.max_value)
        for k in self.fuzzy_sets.keys():
            string += "\n{0}".format(self.fuzzy_sets[k])
        return string
    
    def getDict(self):
        """
        Get the dictionary describing this variable
        """
        d = {'name':self.name}
        d['fuzzy_sets'] = {}
        for fs in self.fuzzy_sets:
            d['fuzzy_sets'][fs] = self.fuzzy_sets[fs].getDict()[fs]
        return d
        
class FuzzyBooleanVariable(object):
    """
    A FuzzyVariable has a name and an array of FuzzySet that defines the variable
    """
    def __init__(self, name):
        """
        just give a name to the variable to create it
        """
        self.name = name
        self.max_value = 1
        self.min_value = 0
        self.fuzzy_sets = {'True':TriangularFuzzyset([0,1,2],'True'),'False':TriangularFuzzyset([-1,0,1],'False')}
        
    def degree(self, c, fuzzy_set):
        """
        Get the degree of a fuzzyset to a crisp value
        
        Keyword Arguments:
        
        c -- int/float crisp value
        fuzzy_set -- a string containing the name of the fuzzy_set to get the degree of, according to the c crisp value
        """
        crisp = float(c)
        if crisp > self.max_value:
            crisp = self.max_value
        if crisp < self.min_value:
            crisp = self.min_value
        return self.fuzzy_sets[fuzzy_set].degree(crisp)
    
    def get_fuzzysets(self):
        """
        Get the dictionary describing the fuzzysets of this variable
        """
        return sorted([self.fuzzy_sets[x].getDict for x in self.fuzzy_sets.keys() ])
            
    def get_degrees(self,c):
        """
        this method returns a dictionary with all fuzzyset degrees related to the crisp:
        
        {'fuzzyset_name':degree}
        """
        crisp = float(c)
        d = {}
        for k in self.fuzzy_sets.keys():
            d[k] = self.degree(crisp,k)
        return d

    def __str__(self):
        string = "{0}: MIN({1}) - MAX({2})".format(self.name, self.min_value, self.max_value)
        for k in self.fuzzy_sets.keys():
            string += "\n{0}".format(self.fuzzy_sets[k])
        return string
    
    def getDict(self):
        """
        Get the dictionary describing this variable
        """
        d = {'name':self.name}
        d['fuzzy_sets'] = {}
        for fs in self.fuzzy_sets:
            d['fuzzy_sets'][fs] = self.fuzzy_sets[fs].getDict()[fs]
        return d
