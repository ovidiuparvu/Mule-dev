# Define a class which stores spatial entity information

class SpatialEntity:
    """
    Class which stores information for each spatial entity
    """
    
    def __init__(self, name):
        """
        Keyword arguments:
        name -- the name of the spatial entity
        """
        self._name = name
        
    @property
    def name(self):
        """ Get the name of the spatial entity """
        return self._name