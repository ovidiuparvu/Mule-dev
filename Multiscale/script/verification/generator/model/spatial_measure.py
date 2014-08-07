# Define a class which stores spatial measures' information

class SpatialMeasure:
    """
    Class used to store information for spatial measures
    """
    
    def __init__(self, name, description, min_value, max_value):
        """
        Keyword arguments:
        name -- the name of the spatial measure
        description -- the description of the spatial measure
        min_value -- the minimum valid spatial measure value
        max_value -- the maximum valid spatial measure value
        """
        self._name = name
        self._description = description
        self._min_value = min_value
        self._max_value = max_value
        
    @property
    def name(self):
        """ Get the name of the spatial measure """
        return self._name
    
    @property
    def description(self):
        """ Get the description of the spatial measure """
        return self._description
    
    @property
    def min_value(self):
        """ Get the spatial measure minimum valid value """
        return self._min_value
    
    @property
    def max_value(self):
        """ Get the spatial measure maximum valid value """
        return self._max_value