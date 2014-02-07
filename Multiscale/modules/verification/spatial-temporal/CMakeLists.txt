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


# ParserTest

set(PARSER_TEST_SRC
    src/Parser.cpp
    src/evaluation/AndEvaluator.cpp
    src/evaluation/EquivalenceEvaluator.cpp
    src/evaluation/ImplicationEvaluator.cpp
    src/evaluation/OrEvaluator.cpp
    src/exception/ParserGrammarExceptionHandler.cpp
    
    test/ParserTest.cpp
)

add_executable(ParserTest ${PARSER_TEST_SRC})
AddUnitTest(ParserTest)

target_link_libraries(ParserTest gtest gtest_main)


# ParserGrammarSample

set(PARSER_GRAMMAR_SAMPLE_SRC
    src/Parser.cpp
    src/Parser.cpp
    src/evaluation/AndEvaluator.cpp
    src/evaluation/EquivalenceEvaluator.cpp
    src/evaluation/ImplicationEvaluator.cpp
    src/evaluation/OrEvaluator.cpp
    src/exception/ParserGrammarExceptionHandler.cpp
     
    sample/ParserGrammarSample.cpp 
)

add_executable(ParserGrammarSample ${PARSER_GRAMMAR_SAMPLE_SRC})
AddSample(ParserGrammarSample)


# EmployeeSample

set(EMPLOYEE_SAMPLE_SRC
   sample/Employee.cpp 
)

add_executable(EmployeeSample ${EMPLOYEE_SAMPLE_SRC})
AddSample(EmployeeSample)