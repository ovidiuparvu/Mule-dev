import os
import re
import shutil
import sys

import jinja2.environment, jinja2.loaders

import model
import parsing


# Constants definitions

ERR_INCORRECT_NR_ARGS = "Usage: generator.py <xml_file_path> <xml_schema_file_path>"

ERR_INVALID_XML_BEGIN = "The xml configuration file \""
ERR_INVALID_XML_MIDDLE = "\" is not valid with respect to the xml schema file \""
ERR_INVALID_XML_END = "\"."
  
ERR_INVALID_PATH_BEGIN = "The provided path \""
ERR_INVALID_PATH_END = "\" is invalid. Please change."
  
# Auto-generated file warning message
WRN_AUTO_GENERATED_FILE = [
"*",
"* WARNING! AUTO-GENERATED FILE.",
"*",
"* PLEASE DO NOT UPDATE THIS FILE MANUALLY. ",
"* USE THE PYTHON GENERATOR SCRIPTS FOR ANY MODIFICATIONS.",
"*"
]
  
PROJECT_ROOT_FOLDER = "/home/ovidiu/Repositories/git/multiscale/Multiscale"
TEMPLATES_FOLDER_PATH = PROJECT_ROOT_FOLDER + "/script/verification/generator/templates"

TAG_WRN_AUTO_GENERATED_FILE = "auto_generated_warning"

TAG_SPATIAL_ENTITIES = "spatial_entities"
TAG_SPATIAL_MEASURES = "spatial_measures"
TAG_SPATIAL_ENTITY_NAME = "spatial_entity_name"

TAG_SPATIAL_ENTITY_NAME_FIXED_WIDTH = "#spatial_entity_fixed_width"
TAG_SPATIAL_MEASURE_NAME_FIXED_WIDTH = "#spatial_measure_fixed_width"

TAG_FILTER_FIRST_TO_UPPER = "first_to_upper"

FIXED_WIDTH_PADDING = 4

EXT_HEADER_FILE = ".hpp"
EXT_SOURCE_FILE = ".cpp"

# List of (input_template_path, output_template_path, min_spatial_entity_width, min_spatial_measure_width)
TEMPLATE_PREPROCESSING_IO = [
    (PROJECT_ROOT_FOLDER + "/script/verification/generator/templates/spatial_measure_type_hpp.tpl.in", PROJECT_ROOT_FOLDER + "/script/verification/generator/templates/spatial_measure_type_hpp.tpl", 1, 29),
    (PROJECT_ROOT_FOLDER + "/script/verification/generator/templates/subset_specific_type_hpp.tpl.in", PROJECT_ROOT_FOLDER + "/script/verification/generator/templates/subset_specific_type_hpp.tpl", 29, 1),
    (PROJECT_ROOT_FOLDER + "/script/verification/generator/templates/symbol_tables_auto_generated_hpp.tpl.in", PROJECT_ROOT_FOLDER + "/script/verification/generator/templates/symbol_tables_auto_generated_hpp.tpl", 1, 1)
]

# Dictionary of (template_path, generated_source_file_path)
SOURCE_FILE_GENERATING_IO = {
    "mstml_l1v1_xsd.tpl" : PROJECT_ROOT_FOLDER + "/config/verification/spatial-temporal/schema/MSTML_L1V1.xsd",
    "spatial_measure_attribute_auto_generated_cpp.tpl" : PROJECT_ROOT_FOLDER + "/modules/verification/spatial-temporal/src/attribute/SpatialMeasureAttributeAutoGenerated.cpp",
    "spatial_measure_type_hpp.tpl" : PROJECT_ROOT_FOLDER + "/modules/verification/spatial-temporal/include/multiscale/verification/spatial-temporal/attribute/SpatialMeasureType.hpp",
    "spatial_temporal_data_reader_auto_generated_cpp.tpl" : PROJECT_ROOT_FOLDER + "/modules/verification/spatial-temporal/src/data/SpatialTemporalDataReaderAutoGenerated.cpp",
    "subset_specific_attribute_auto_generated_cpp.tpl" : PROJECT_ROOT_FOLDER + "/modules/verification/spatial-temporal/src/attribute/SubsetSpecificAttributeAutoGenerated.cpp",
    "subset_specific_type_hpp.tpl" : PROJECT_ROOT_FOLDER + "/modules/verification/spatial-temporal/include/multiscale/verification/spatial-temporal/attribute/SubsetSpecificType.hpp",
    "symbol_tables_auto_generated_hpp.tpl" : PROJECT_ROOT_FOLDER + "/modules/verification/spatial-temporal/include/multiscale/verification/spatial-temporal/parsing/SymbolTablesAutoGenerated.hpp"
}

DERIVED_SPATIAL_ENTITY_TEMPLATE_PATH = "derived_spatial_entity_hpp.tpl"
DERIVED_SPATIAL_ENTITY_OUTPUT_FOLDER = PROJECT_ROOT_FOLDER + "/modules/verification/spatial-temporal/include/multiscale/verification/spatial-temporal/model/"


# Functions definitions

def validate_path(path):
    """ Check if the input path is valid """
    if isinstance(path, str) and len(path) > 0:
        if os.path.exists(path):
            return True
      
    # Else raise invalid value error  
    raise ValueError(ERR_INVALID_PATH_BEGIN + path + ERR_INVALID_PATH_END)

def generate_derived_spatial_entity_file(environment, template_path, output_folder, spatial_entity_name):
    """Generate the source file
    
    Keyword argument:
    environment -- the environment for loading templates
    template_path -- path to the template file
    output_folder -- path to the output folder
    spatial_entity_name -- the name of the spatial entity
    """
    # Assert the validity of the input parameters
    assert environment is not None
    assert isinstance(template_path, str) and len(template_path) > 0
    assert isinstance(output_folder, str) and len(output_folder) > 0
    assert isinstance(spatial_entity_name, str) and len(spatial_entity_name) > 0
    
    # Load and get a reference to the template
    template = environment.get_template(template_path)
    
    # Initialise output_path
    output_path = output_folder + first_to_upper(spatial_entity_name) + EXT_HEADER_FILE
    
    # Generate source file from template
    with open(output_path, "w+") as output_file:
        output_file.write(
            template.render({
                TAG_SPATIAL_ENTITY_NAME : spatial_entity_name,
                TAG_WRN_AUTO_GENERATED_FILE : WRN_AUTO_GENERATED_FILE
            })
        )

def generate_spatial_entities_and_measures_dependent_file(environment, template_path, 
                                                          output_path, spatial_entities, 
                                                          spatial_measures):
    """Generate the source file dependent on the collection of spatial
    entities and spatial measures
    
    Keyword argument:
    environment -- the environment for loading templates
    template_path -- path to the template file
    output_path -- path to the output file
    spatial_entities -- the list of spatial entities
    spatial_measures -- the list of spatial measures
    """
    # Assert the validity of the input parameters
    assert environment is not None
    assert isinstance(template_path, str) and len(template_path) > 0
    assert isinstance(output_path, str) and len(output_path) > 0
    assert isinstance(spatial_entities, list) and len(spatial_entities) > 0
    assert isinstance(spatial_measures, list) and len(spatial_measures) > 0
    
    # Load and get a reference to the template
    template = environment.get_template(template_path)
    
    # Generate source file from template
    with open(output_path, "w+") as output_file:
        output_file.write(
            template.render({
                TAG_SPATIAL_ENTITIES : spatial_entities, 
                TAG_SPATIAL_MEASURES : spatial_measures,
                TAG_WRN_AUTO_GENERATED_FILE : WRN_AUTO_GENERATED_FILE
            })
        )


def first_to_upper(input_string):
    """Return the input string with the first letter uppercase
    
    Keyword arguments:
    input_string -- the input string whose first letter will be uppercase
    """
    if isinstance(input_string, str): 
        if len(input_string) > 1:
            return (input_string[:1].capitalize()) + (input_string[1:])
        else:
            return input_string
    else:
        raise TypeError("The input parameter input_string should be of type str. Please change.")

def preprocess_template_file(input_file_path, output_file_path, spatial_entities, spatial_measures,
                             min_spatial_entity_width=1, min_spatial_measure_width=1):
    """ Preprocess the given input template and generate the output template
    
    Keyword arguments:
    input_file_path -- template input file path
    output_file_path -- template output file path
    spatial_entities -- list of spatial entities
    spatial_measures -- list of spatial measures
    """
    # Assert the validity of the input
    assert isinstance(input_file_path, str) and len(input_file_path) > 0
    assert isinstance(output_file_path, str) and len(output_file_path) > 0
    assert isinstance(spatial_entities, list) and len(spatial_entities) > 0
    assert isinstance(spatial_measures, list) and len(spatial_measures) > 0
    
    # Compute the maximum width for spatial entities and spatial measures names
    spatial_entity_fixed_width = max(
        max([len(spatial_entity.name) for spatial_entity in spatial_entities]), 
        min_spatial_entity_width
    ) + FIXED_WIDTH_PADDING
    spatial_measure_fixed_width = max(
        max([len(spatial_measure.name) for spatial_measure in spatial_measures]),
        min_spatial_measure_width
    ) + FIXED_WIDTH_PADDING
    
    # Create the replace dictionary
    replace_dictionary = {
        TAG_SPATIAL_ENTITY_NAME_FIXED_WIDTH : str(spatial_entity_fixed_width), 
        TAG_SPATIAL_MEASURE_NAME_FIXED_WIDTH : str(spatial_measure_fixed_width)
    }
    
    # Create the replacement regular expression
    regular_expression = re.compile("|".join(replace_dictionary.keys()))
    
    # Create output file
    with open(output_file_path, "w+") as output_file:
        with open(input_file_path, "r") as input_file:
            for line in input_file:
                output_file.write(
                    regular_expression.sub(
                        lambda matched_token: replace_dictionary[matched_token.group(0)], 
                        line
                    )
                )
        

def generate_source_files(spatial_entities, spatial_measures):
    """Generate the source files considering the given spatial entities 
    and spatial measures
    
    Keyword arguments:
    spatial_entities -- the list of spatial entities
    spatial_measure -- the list of spatial measures
    """
    # Assert that the spatial_entities and spatial_measures lists have more than one element
    assert isinstance(spatial_entities, list) and len(spatial_entities) > 0
    assert isinstance(spatial_measures, list) and len(spatial_measures) > 0
    
    # Load the environment with all required templates
    environment = jinja2.environment.Environment(
                      loader=jinja2.loaders.FileSystemLoader(TEMPLATES_FOLDER_PATH),
                      trim_blocks=True,
                      lstrip_blocks=True
                  )
    
    # Register the first_to_upper custom filter
    environment.filters[TAG_FILTER_FIRST_TO_UPPER] = first_to_upper
    
    # Preprocess all dependent template input files
    for (template_input_file, template_output_file, min_spatial_entity_width, min_spatial_measure_width) in TEMPLATE_PREPROCESSING_IO:
        preprocess_template_file(template_input_file, template_output_file, 
                                 spatial_entities, spatial_measures, min_spatial_entity_width,
                                 min_spatial_measure_width)
    
    # Generate the spatial entities and measures dependent files
    for template_path, output_path in SOURCE_FILE_GENERATING_IO.iteritems():
        generate_spatial_entities_and_measures_dependent_file(environment, template_path, 
                                                              output_path, spatial_entities, 
                                                              spatial_measures)
    
    # Generate the derived spatial entity files
    for spatial_entity in spatial_entities:
        generate_derived_spatial_entity_file(environment, DERIVED_SPATIAL_ENTITY_TEMPLATE_PATH, 
                                             DERIVED_SPATIAL_ENTITY_OUTPUT_FOLDER, spatial_entity.name)


def parse_configuration_file(xml_file_path, xml_schema_path):
    """Parse the configuration file and return the list of spatial entities 
    and spatial measures

    Keyword arguments:
    xml_file_path -- xml configuration file path
    xml_schema_path -- xml configuration schema file path  
    
    Returns (parse_result, spatial_entities, spatial_measures) where:
        - parse_result: Result of parsing the xml file (True/False)
        - spatial_entities: The list of spatial entities recorded in the xml file
        - spatial_measures: The list of spatial measures recorded in the xml file
    """
    # Assert that the paths are non-empty strings
    assert isinstance(xml_file_path, str) and len(xml_file_path) > 0
    assert isinstance(xml_schema_path, str) and len(xml_schema_path) > 0
    
    # Construct xml parser
    parser = parsing.parser.SpatialDescriptionParser(xml_file_path, xml_schema_path)
    
    # Parse the spatial description
    if parser.parse():
        return (True, parser.spatial_entities, parser.spatial_measures)
    else:
        return (False, [], [])

def parse_configuration_and_generate_files(xml_file_path, xml_schema_path):
    """Parse the configuration file and generate all spatial description dependent source files
    
    Keyword arguments:
    xml_file_path -- xml configuration file path
    xml_schema_path -- xml configuration schema file path
    """
    # Check if the paths are valid
    validate_path(xml_file_path)
    validate_path(xml_schema_path)
        
    # Parse configuration file
    (parse_result, spatial_entities, spatial_measures) = parse_configuration_file(xml_file_path, xml_schema_path)
    
    # If successful then generate source files
    if parse_result:
       generate_source_files(spatial_entities, spatial_measures) 
    else:
        raise RuntimeError(ERR_INVALID_XML_BEGIN + xml_file_path + 
                           ERR_INVALID_XML_MIDDLE + xml_schema_path + 
                           ERR_INVALID_XML_END)

# Do the following whenever the script is executed
if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(ERR_INCORRECT_NR_ARGS)
    else:
        parse_configuration_and_generate_files(sys.argv[1], sys.argv[2])
    
