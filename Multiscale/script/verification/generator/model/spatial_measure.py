# Define a class which stores spatial measures' information


class SpatialMeasure:
    """
    Class used to store information for spatial measures
    """
    
    def __init__(self, name, description, minValue, maxValue):
        """
        Keyword arguments:
        name -- the name of the spatial measure
        description -- the description of the spatial measure
        minValue -- the minimum valid spatial measure value
        maxValue -- the maximum valid spatial measure value
        """
        self._name = name
        self._description = description
        self._minValue = minValue
        self._maxValue = maxValue
        
    @property
    def name(self):
        """ Get the name of the spatial measure """
        return self._name
    
    @property
    def description(self):
        """ Get the description of the spatial measure """
        return self._description
    
    @property
    def minValue(self):
        """ Get the spatial measure minimum valid value """
        return self._minValue
    
    @property
    def maxValue(self):
        """ Get the spatial measure maximum valid value """
        return self._maxValue