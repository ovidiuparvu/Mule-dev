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
# Generate source files considering spatial_description 
# generator configuration file 
#------------------------------------------------------------

# Add a custom command which specifies which source files are generated
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/model/SpatialEntity.cpp
    COMMAND python "${PROJECT_SOURCE_DIR}/script/verification/generator/generator.py"
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/model/SpatialEntity.cpp 
    MAIN_DEPENDENCY "${PROJECT_SOURCE_DIR}/config/verification/spatial-temporal/generator/spatial_description.xml"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


#------------------------------------------------------------
# Add executables
#------------------------------------------------------------


# MultidimensionalMultiscaleModelChecker

# Update the build number of the model checker
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/checking/ModelCheckingOutputWriter.cpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/src/checking/ModelCheckingOutputWriter.cpp
)

# Set the path to the MSTML xml schema definition file
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/data/SpatialTemporalDataReader.cpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/src/data/SpatialTemporalDataReader.cpp
)

# Set the dependencies for the model checker
set(MULTIDIMENSIONAL_MULTISCALE_MODEL_CHECKER_SRC
    src/data/LogicPropertyDataReader.cpp
    src/data/SpatialTemporalDataReader.cpp
    
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

    src/checking/ApproximateBayesianModelChecker.cpp
    src/checking/ApproximateBayesianModelCheckerFactory.cpp    
    src/checking/ApproximateProbabilisticModelChecker.cpp
    src/checking/ApproximateProbabilisticModelCheckerFactory.cpp    
    src/checking/BayesianModelChecker.cpp
    src/checking/BayesianModelCheckerFactory.cpp    
    src/checking/ModelChecker.cpp
    src/checking/ModelCheckingManager.cpp
    src/checking/ModelCheckingOutputWriter.cpp
    src/checking/ProbabilisticBlackBoxModelChecker.cpp
    src/checking/ProbabilisticBlackBoxModelCheckerFactory.cpp
    src/checking/StatisticalModelChecker.cpp
    src/checking/StatisticalModelCheckerFactory.cpp
    
    src/exception/ParserGrammarExceptionHandler.cpp
    
    src/execution/CommandLineModelChecking.cpp
    
    src/model/AbstractSyntaxTree.cpp
    src/model/SpatialEntity.cpp
    src/model/SpatialTemporalTrace.cpp
    src/model/TimePoint.cpp
    
    src/parsing/Parser.cpp
    
    src/Mule.cpp 
)

AddExecutableInstallTarget(Mule "${MULTIDIMENSIONAL_MULTISCALE_MODEL_CHECKER_SRC}")
AddDebugPostfix(Mule)

target_link_libraries(Mule util)
target_link_libraries(Mule ${XERCESC_LIBRARY})


# ModelCheckerTest

set(MODEL_CHECKER_TEST_SRC
    src/data/LogicPropertyDataReader.cpp
    src/data/SpatialTemporalDataReader.cpp
    
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

    src/checking/ApproximateBayesianModelChecker.cpp
    src/checking/ApproximateBayesianModelCheckerFactory.cpp    
    src/checking/ApproximateProbabilisticModelChecker.cpp
    src/checking/ApproximateProbabilisticModelCheckerFactory.cpp    
    src/checking/BayesianModelChecker.cpp
    src/checking/BayesianModelCheckerFactory.cpp    
    src/checking/ModelChecker.cpp
    src/checking/ProbabilisticBlackBoxModelChecker.cpp
    src/checking/ProbabilisticBlackBoxModelCheckerFactory.cpp
    src/checking/StatisticalModelChecker.cpp
    src/checking/StatisticalModelCheckerFactory.cpp
    
    src/exception/ParserGrammarExceptionHandler.cpp
    
    src/model/AbstractSyntaxTree.cpp
    src/model/SpatialEntity.cpp
    src/model/SpatialTemporalTrace.cpp
    src/model/TimePoint.cpp
    
    src/parsing/Parser.cpp
    
    test/checking/ModelCheckingTest.cpp
)

add_executable(ModelCheckingTest ${MODEL_CHECKER_TEST_SRC})
AddUnitTest(ModelCheckingTest)

target_link_libraries(ModelCheckingTest util)
target_link_libraries(ModelCheckingTest gtest gtest_main)


# ParserEvaluationTest

set(PARSER_EVALUATION_TEST_SRC
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
    
    src/parsing/Parser.cpp
    
    test/evaluation/ParserEvaluationTest.cpp
)

add_executable(ParserEvaluationTest ${PARSER_EVALUATION_TEST_SRC})
AddUnitTest(ParserEvaluationTest)

target_link_libraries(ParserEvaluationTest util)
target_link_libraries(ParserEvaluationTest gtest gtest_main)


# ParserTest

set(PARSER_TEST_SRC
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
    
    src/parsing/Parser.cpp
    
    test/parsing/ParserTest.cpp
)

add_executable(ParserTest ${PARSER_TEST_SRC})
AddUnitTest(ParserTest)

target_link_libraries(ParserTest util)
target_link_libraries(ParserTest gtest gtest_main)


# ParserSample

set(PARSER_SAMPLE_SRC
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
    
    src/parsing/Parser.cpp
    
    sample/ParserSample.cpp 
)


# ParserEvaluationSample

set(PARSER_EVALUATION_SAMPLE_SRC
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
    
    src/parsing/Parser.cpp
    
    sample/ParserEvaluationSample.cpp 
)

add_executable(ParserEvaluationSample ${PARSER_EVALUATION_SAMPLE_SRC})
AddSample(ParserEvaluationSample)

target_link_libraries(ParserEvaluationSample util)


# LogicPropertyDataReaderSample

set(LOGIC_PROPERTY_DATA_READER_SAMPLE_SRC
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

    src/data/LogicPropertyDataReader.cpp

    src/exception/ParserGrammarExceptionHandler.cpp
    
    src/model/AbstractSyntaxTree.cpp
    src/model/SpatialEntity.cpp
    src/model/SpatialTemporalTrace.cpp
    src/model/TimePoint.cpp
    
    src/parsing/Parser.cpp
    
    sample/LogicPropertyDataReaderSample.cpp
)

add_executable(LogicPropertyDataReaderSample ${LOGIC_PROPERTY_DATA_READER_SAMPLE_SRC})
AddSample(LogicPropertyDataReaderSample)

target_link_libraries(LogicPropertyDataReaderSample util)


# SpatialTemporalDataReaderSample

set(SPATIAL_TEMPORAL_DATA_READER_SAMPLE_SRC
    src/attribute/SubsetSpecificAttribute.cpp
        
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