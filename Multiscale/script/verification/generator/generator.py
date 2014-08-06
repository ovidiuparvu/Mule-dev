import os
import shutil
import sys

import model
import parsing


# Generate all spatial description dependent source files for the project
def generateSourceFiles(relative_source_path, relative_destination_path):
    # Construct xml parser
    parser = parsing.parser.SpatialDescriptionParser(relative_source_path, relative_destination_path)
    
    # Parse the spatial description
    if parser.parse():
        print("The xml file is valid.")
    else:
        print("The xml file is invalid according to the xml schema specification. Please change.")


# Do the following whenever the script is executed
if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: generator.py <xml_file_path> <xml_schema_file_path>")
    else:
        generateSourceFiles(sys.argv[1], sys.argv[2])
    