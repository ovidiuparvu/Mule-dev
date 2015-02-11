import os

import lxml.etree

import model.spatial_entity
import model.spatial_measure


# Constants definitions

ERR_INVALID_PATH_BEGIN = "The provided path \""
ERR_INVALID_PATH_END = "\" is invalid. Please change."

XPATH_SPATIAL_ENTITY = ".//spatialEntity"
XPATH_SPATIAL_MEASURE = ".//spatialMeasure"

TAG_NAME = "name"
TAG_DESCRIPTION = "description"
TAG_MIN_VALUE = "minValue"
TAG_MAX_VALUE = "maxValue"


# Define the class for parsing spatial descriptions

class SpatialDescriptionParser:
    """
    Class used to parse spatial descriptions  
    """
    
    def __init__(self, xml_file_path, xml_schema_path):
        """Construct a spatial description parser.  
        
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
        # Validate the xml (schema) file path
        self._validate_file_path(self._xml_file_path) 
        self._validate_file_path(self._xml_schema_path)
        
        # Parse the xml and check its validity
        if self._is_valid_xml():
            self._parse_spatial_entities()
            self._parse_spatial_measures()
            
            return True
        else:
            return False
        
    def _validate_file_path(self, file_path):
        """Check if the given file path is valid 
        
        Keyword arguments:
        file_path -- the path to the file to be validated
        """
        if isinstance(file_path, str) and len(file_path) > 0:
            if os.path.exists(file_path):
                return True
          
        # Else raise invalid value error  
        raise ValueError(
            ERR_INVALID_PATH_BEGIN + file_path + ERR_INVALID_PATH_END
        )
        
    def _is_valid_xml(self):
        """ Check if the xml file is valid according to the given schema """
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
        
        for spatial_entity_element in (
            self._xml_tree_root.findall(XPATH_SPATIAL_ENTITY)
        ):
            spatial_entity_name = spatial_entity_element.find(TAG_NAME).text
            
            self._spatial_entities.append(
                model.spatial_entity.SpatialEntity(spatial_entity_name)
            )
            
    def _parse_spatial_measures(self):
        """
        Construct a collection of spatial measures from the xml tree
        """
        self._spatial_measures = []
        
        for spatial_measure_element in (
            self._xml_tree_root.findall(XPATH_SPATIAL_MEASURE)
        ):
            spatial_measure_name = (
                spatial_measure_element.find(TAG_NAME).text
            )
            spatial_measure_description = (
                spatial_measure_element.find(TAG_DESCRIPTION).text
            )
            spatial_measure_min_value = (
                spatial_measure_element.find(TAG_MIN_VALUE).text
            )
            spatial_measure_max_value = (
                spatial_measure_element.find(TAG_MAX_VALUE).text
            )
            
            self._spatial_measures.append(
                model.spatial_measure.SpatialMeasure(
                    spatial_measure_name,
                    spatial_measure_description,
                    spatial_measure_min_value,
                    spatial_measure_max_value,
                )
            )