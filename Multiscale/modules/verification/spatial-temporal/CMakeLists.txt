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


# ParserGrammar 

set(PARSER_GRAMMAR_SRC
    src/ParserGrammar.cpp 
)

add_executable(ParserGrammar ${PARSER_GRAMMAR_SRC})

AddDebugPostfix(ParserGrammar)

# target_link_libraries(ParserGrammar util)
# target_link_libraries(ParserGrammar ${Boost_PROGRAM_OPTIONS_LIBRARY})