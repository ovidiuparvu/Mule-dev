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


# ParserEvaluationTest

#set(PARSER_EVALUATION_TEST_SRC
#    src/Parser.cpp
#    src/exception/ParserGrammarExceptionHandler.cpp
#    
#    test/ParserEvaluationTest.cpp
#)
#
#add_executable(ParserEvaluationTest ${PARSER_EVALUATION_TEST_SRC})
#AddUnitTest(ParserEvaluationTest)
#
#target_link_libraries(ParserEvaluationTest gtest gtest_main)


# ParserTest

set(PARSER_TEST_SRC
    src/Parser.cpp
    
    src/attribute/BinaryNumericMeasureAttribute.cpp
    src/attribute/BinarySubsetMeasureAttribute.cpp
    src/attribute/ComparatorAttribute.cpp
    src/attribute/ProbabilisticLogicPropertyAttribute.cpp
    src/attribute/QuaternarySubsetMeasureAttribute.cpp
    src/attribute/SpatialMeasureAttribute.cpp
    src/attribute/SubsetSpecificAttribute.cpp
    src/attribute/TernarySubsetMeasureAttribute.cpp
    src/attribute/UnaryNumericMeasureAttribute.cpp
    src/attribute/UnarySubsetMeasureAttribute.cpp
    
    src/exception/ParserGrammarExceptionHandler.cpp
    
    test/ParserTest.cpp
)

add_executable(ParserTest ${PARSER_TEST_SRC})
AddUnitTest(ParserTest)

target_link_libraries(ParserTest gtest gtest_main)


# ParserGrammarSample

set(PARSER_GRAMMAR_SAMPLE_SRC
    src/Parser.cpp
    
    src/attribute/BinaryNumericMeasureAttribute.cpp
    src/attribute/BinarySubsetMeasureAttribute.cpp
    src/attribute/ComparatorAttribute.cpp
    src/attribute/ProbabilisticLogicPropertyAttribute.cpp
    src/attribute/QuaternarySubsetMeasureAttribute.cpp
    src/attribute/SpatialMeasureAttribute.cpp
    src/attribute/SubsetSpecificAttribute.cpp
    src/attribute/TernarySubsetMeasureAttribute.cpp
    src/attribute/UnaryNumericMeasureAttribute.cpp
    src/attribute/UnarySubsetMeasureAttribute.cpp

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