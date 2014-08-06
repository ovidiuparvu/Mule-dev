import os
import shutil
import sys

import jinja2.environment, jinja2.loaders

import model
import parsing


# Constants definitions
MSTML_TEMPLATE_PATH = "mstml_l1v1.tpl"
MSTML_OUTPUT_PATH = "/home/ovidiu/Repositories/git/multiscale/Multiscale/config/verification/spatial-temporal/schema/MSTML_L1V1.xsd"

# Generate the source file
#
# Keyword argument:
# environment -- the environment in which templates were loaded
# template_path -- path to the template file
# output_path -- path to the output file
# spatial_entities -- the list of spatial entities
# spatial_measure -- the list of spatial measures
def generate_file(environment, template_path, output_path, spatial_entities, spatial_measures):
    template = environment.get_template(template_path)
    
    with open(output_path, "w+") as output_file:
        output_file.write(
            template.render({
                'spatial_entities' : spatial_entities, 
                'spatial_measures' : spatial_measures
            })
        )

# Return the input string with the first letter uppercase
#
# Keyword arguments:
# input_string -- the input string
def _first_to_upper(input_string):
    return (input_string[:1].capitalize()) + (input_string[1:]) 

# Generate the source files considering the given spatial entities and spatial measures
#
# Keyword arguments:
# spatial_entities -- the list of spatial entities
# spatial_measure -- the list of spatial measures
def generate_source_files(spatial_entities, spatial_measures):
    # Load the environment with all required templates
    environment = jinja2.environment.Environment(
                      loader=jinja2.loaders.FileSystemLoader("templates"),
                      trim_blocks=True,
                      lstrip_blocks=True
                  )
    
    # Register the first_to_upper custom filter
    environment.filters['first_to_upper'] = _first_to_upper
    
    # Generate the source files
    generate_file(environment, MSTML_TEMPLATE_PATH, MSTML_OUTPUT_PATH, spatial_entities, spatial_measures)

# Parse the configuration file and return the list of spatial entities and spatial measures
#
# Keyword arguments:
# xml_file_path -- xml configuration file path
# xml_schema_path -- xml configuration schema file path  
#
# Returns (parse_result, spatial_entities, spatial_measures) where:
#     - parse_result: Result of parsing the xml file (True/False)
#     - spatial_entities: The list of spatial entities recorded in the xml file
#     - spatial_measures: The list of spatial measures recorded in the xml file
def parse_configuration_file(xml_file_path, xml_schema_path):
    # Construct xml parser
    parser = parsing.parser.SpatialDescriptionParser(xml_file_path, xml_schema_path)
    
    # Parse the spatial description
    if parser.parse():
        return (True, parser.spatial_entities, parser.spatial_measures)
    else:
        return (False, [], [])
        
# Parse the configuration file and generate all spatial description dependent source files
#
# Keyword arguments:
# xml_file_path -- xml configuration file path
# xml_schema_path -- xml configuration schema file path
def parse_configuration_and_generate_files(xml_file_path, xml_schema_path):
    (parse_result, spatial_entities, spatial_measures) = parse_configuration_file(xml_file_path, xml_schema_path)
    
    if parse_result:
       generate_source_files(spatial_entities, spatial_measures) 
    else:
        raise RuntimeError("The xml configuration file " + 
                           xml_file_path + 
                           " is not valid with respect to the xml schema file " + 
                           xml_schema_path + 
                           ".")


# Do the following whenever the script is executed
if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: generator.py <xml_file_path> <xml_schema_file_path>")
    else:
        parse_configuration_and_generate_files(sys.argv[1], sys.argv[2])
    