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

# PolarMapCsvToInputFiles

set(POLAR_MAP_CSV_TO_INPUT_FILES_SRC
    src/PolarMapCsvToInputFiles.cpp
    src/PolarCsvToInputFilesConverter.cpp   
)

AddExecutableInstallTarget(PolarMapCsvToInputFiles "${POLAR_MAP_CSV_TO_INPUT_FILES_SRC}")
AddDebugPostfix(PolarMapCsvToInputFiles)

target_link_libraries(PolarMapCsvToInputFiles util)
target_link_libraries(PolarMapCsvToInputFiles ${Boost_PROGRAM_OPTIONS_LIBRARY})


# MapCartesianToPolarScript

# Set the paths to the script header, content and footer template
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PolarGnuplotScriptGenerator.cpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PolarGnuplotScriptGenerator.cpp
)

set(MAP_CARTESIAN_TO_POLAR_SCRIPT
    src/AnnularSector.cpp
    src/CartesianToPolarConverter.cpp
    src/MapCartesianToPolarScript.cpp
    src/PolarGnuplotScriptGenerator.cpp
)

AddExecutableInstallTarget(MapCartesianToPolarScript "${MAP_CARTESIAN_TO_POLAR_SCRIPT}")
AddDebugPostfix(MapCartesianToPolarScript)

target_link_libraries(MapCartesianToPolarScript util)
target_link_libraries(MapCartesianToPolarScript ${Boost_PROGRAM_OPTIONS_LIBRARY})
