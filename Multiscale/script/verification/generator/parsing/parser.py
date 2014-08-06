import lxml.etree

import model.spatial_entity
import model.spatial_measure


# Define the class for parsing spatial descriptions

class SpatialDescriptionParser:
    """
    Class used to parse spatial descriptions  
    """
    
    def __init__(self, xml_file_path, xml_schema_path):
        """ 
        Construct a spatial description parser.  
        
        Keyword arguments:
        xmlFilePath -- the xml file path
        xmlSchemaPath -- the xml schema file path
        """
        
        self._xml_file_path = xml_file_path
        self._xml_schema_path = xml_schema_path
        
    @property
    def spatial_entities(self):
        """ Get the list of spatial entities """
        return self._spatial_entities
    
    @property
    def spatial_measures(self):
        """ Get the list of spatial measures """
        return self._spatial_measures
        
    def parse(self):
        """
        Validate the given xml file against the given schema
        
        Return true if the xml file is valid, and false otherwise.
        """
        if self._is_valid_xml():
            self._parse_spatial_entities()
            self._parse_spatial_measures()
            
            return True
        else:
            return False
        
    def _is_valid_xml(self):
        """
        Check if the xml file is valid according to the given schema
        """
        xml_tree = lxml.etree.parse(self._xml_file_path)
        self._xml_tree_root = xml_tree.getroot()

        xml_schema_tree = lxml.etree.parse(self._xml_schema_path)
        xml_schema = lxml.etree.XMLSchema(xml_schema_tree)
                
        return xml_schema.validate(xml_tree)
    
    def _parse_spatial_entities(self):
        """
        Construct a collection of spatial entities from the xml tree
        """
        self._spatial_entities = []
        
        for spatial_entity_element in self._xml_tree_root.findall(".//spatialEntity"):
            spatial_entity_name = spatial_entity_element.find("name").text
            
            self._spatial_entities.append(
                model.spatial_entity.SpatialEntity(spatial_entity_name)
            )
            
    def _parse_spatial_measures(self):
        """
        Construct a collection of spatial measures from the xml tree
        """
        self._spatial_measures = []
        
        for spatial_measure_element in self._xml_tree_root.findall(".//spatialMeasure"):
            spatial_measure_name = spatial_measure_element.find("name").text
            spatial_measure_description = spatial_measure_element.find("description").text
            spatial_measure_min_value = spatial_measure_element.find("minValue").text
            spatial_measure_max_value = spatial_measure_element.find("maxValue").text
            
            self._spatial_measures.append(
                model.spatial_measure.SpatialMeasure(
                    spatial_measure_name,
                    spatial_measure_description,
                    spatial_measure_min_value,
                    spatial_measure_max_value,
                )
            )