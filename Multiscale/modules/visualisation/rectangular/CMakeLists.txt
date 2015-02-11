#------------------------------------------------------------
# Include directories
#------------------------------------------------------------

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


#------------------------------------------------------------
# Specify link directories
#------------------------------------------------------------

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/util)


#------------------------------------------------------------
# Add executables
#------------------------------------------------------------


# RectangularMapCsvToInputFiles

set(RECTANGULAR_MAP_CSV_TO_INPUT_FILES_SRC
    src/RectangularMapCsvToInputFiles.cpp
    src/RectangularCsvToInputFilesConverter.cpp   
)

AddExecutableInstallTarget(RectangularMapCsvToInputFiles "${RECTANGULAR_MAP_CSV_TO_INPUT_FILES_SRC}")
AddDebugPostfix(RectangularMapCsvToInputFiles)

target_link_libraries(RectangularMapCsvToInputFiles util)
target_link_libraries(RectangularMapCsvToInputFiles ${Boost_PROGRAM_OPTIONS_LIBRARY})


# RectangularMapEntityCsvToInputFiles

set(RECTANGULAR_MAP_ENTITY_CSV_TO_INPUT_FILES_SRC
    src/RectangularMapEntityCsvToInputFiles.cpp
    src/RectangularEntityCsvToInputFilesConverter.cpp   
)

AddExecutableInstallTarget(RectangularMapEntityCsvToInputFiles "${RECTANGULAR_MAP_ENTITY_CSV_TO_INPUT_FILES_SRC}")
AddDebugPostfix(RectangularMapEntityCsvToInputFiles)

target_link_libraries(RectangularMapEntityCsvToInputFiles util)
target_link_libraries(RectangularMapEntityCsvToInputFiles ${Boost_PROGRAM_OPTIONS_LIBRARY})


# MapCartesianToRectangularScript

# Set the paths to the script header, content and footer template
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RectangularGnuplotScriptGenerator.cpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RectangularGnuplotScriptGenerator.cpp
)

set(MAP_CARTESIAN_TO_SCRIPT
    src/CartesianToConcentrationsConverter.cpp
    src/MapCartesianToScript.cpp
    src/RectangularGnuplotScriptGenerator.cpp
)

AddExecutableInstallTarget(MapCartesianToScript "${MAP_CARTESIAN_TO_SCRIPT}")
AddDebugPostfix(MapCartesianToScript)

target_link_libraries(MapCartesianToScript util)
target_link_libraries(MapCartesianToScript ${Boost_PROGRAM_OPTIONS_LIBRARY})
