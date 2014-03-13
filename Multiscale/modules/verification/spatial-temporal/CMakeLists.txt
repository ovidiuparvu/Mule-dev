#------------------------------------------------------------
# Include directories
#------------------------------------------------------------

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test)


#------------------------------------------------------------
# Specify link directories
#------------------------------------------------------------

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/util)


#------------------------------------------------------------
# Add executables
#------------------------------------------------------------


# ParserEvaluationTest

set(PARSER_EVALUATION_TEST_SRC
    src/parsing/Parser.cpp

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
    
    src/model/AbstractSyntaxTree.cpp
    src/model/SpatialEntity.cpp
    src/model/SpatialTemporalTrace.cpp
    src/model/TimePoint.cpp
    
    test/ParserEvaluationTest.cpp
)

add_executable(ParserEvaluationTest ${PARSER_EVALUATION_TEST_SRC})
AddUnitTest(ParserEvaluationTest)

target_link_libraries(ParserEvaluationTest util)
target_link_libraries(ParserEvaluationTest gtest gtest_main)


# ParserTest

set(PARSER_TEST_SRC
    src/parsing/Parser.cpp
    
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
    
    src/model/AbstractSyntaxTree.cpp
    src/model/SpatialEntity.cpp
    src/model/SpatialTemporalTrace.cpp
    src/model/TimePoint.cpp
    
    test/ParserTest.cpp
)

add_executable(ParserTest ${PARSER_TEST_SRC})
AddUnitTest(ParserTest)

target_link_libraries(ParserTest util)
target_link_libraries(ParserTest gtest gtest_main)


# ParserSample

set(PARSER_SAMPLE_SRC
    src/parsing/Parser.cpp
    
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
    
    src/model/AbstractSyntaxTree.cpp
    src/model/SpatialEntity.cpp
    src/model/SpatialTemporalTrace.cpp
    src/model/TimePoint.cpp
    
    sample/ParserSample.cpp 
)


# ParserEvaluationSample

set(PARSER_EVALUATION_SAMPLE_SRC
    src/parsing/Parser.cpp
    
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
    
    src/model/AbstractSyntaxTree.cpp
    src/model/SpatialEntity.cpp
    src/model/SpatialTemporalTrace.cpp
    src/model/TimePoint.cpp
    
    sample/ParserEvaluationSample.cpp 
)

add_executable(ParserEvaluationSample ${PARSER_EVALUATION_SAMPLE_SRC})
AddSample(ParserEvaluationSample)

target_link_libraries(ParserEvaluationSample util)


# LogicPropertyDataReaderSample

set(LOGIC_PROPERTY_DATA_READER_SAMPLE_SRC
    src/data/LogicPropertyDataReader.cpp
    
    src/parsing/Parser.cpp
    
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
    
    src/model/AbstractSyntaxTree.cpp
    src/model/SpatialEntity.cpp
    src/model/SpatialTemporalTrace.cpp
    src/model/TimePoint.cpp
    
    sample/LogicPropertyDataReaderSample.cpp
)

add_executable(LogicPropertyDataReaderSample ${LOGIC_PROPERTY_DATA_READER_SAMPLE_SRC})
AddSample(LogicPropertyDataReaderSample)

target_link_libraries(LogicPropertyDataReaderSample util)


# SpatialTemporalDataReaderSample

set(SPATIAL_TEMPORAL_DATA_READER_SAMPLE_SRC
    src/data/SpatialTemporalDataReader.cpp
    
    src/model/SpatialEntity.cpp
    src/model/SpatialTemporalTrace.cpp
    src/model/TimePoint.cpp

    sample/SpatialTemporalDataReaderSample.cpp
)

add_executable(SpatialTemporalDataReaderSample ${SPATIAL_TEMPORAL_DATA_READER_SAMPLE_SRC})
AddSample(SpatialTemporalDataReaderSample)

target_link_libraries(SpatialTemporalDataReaderSample util)
target_link_libraries(SpatialTemporalDataReaderSample ${XERCESC_LIBRARY})