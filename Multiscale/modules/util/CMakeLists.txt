#------------------------------------------------------------
# Include directories
#------------------------------------------------------------

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


#------------------------------------------------------------
# Add library
#------------------------------------------------------------

# Util library

set(LIB_SRC
    src/ConsolePrinter.cpp
    src/Filesystem.cpp
    src/geometry/MinEnclosingTriangleFinder.cpp
    src/Geometry2D.cpp
    src/NumberIterator.cpp
    src/Numeric.cpp
    src/OperatingSystem.cpp
    src/RGBColourGenerator.cpp
    src/StringManipulator.cpp
    src/XmlValidator.cpp

    src/statistics/BetaDistribution.cpp
    src/statistics/BinomialDistribution.cpp
    src/statistics/Distribution.cpp

    src/iterator/LexicographicNumberIterator.cpp
    src/iterator/StandardNumberIterator.cpp
)

add_library(util STATIC ${LIB_SRC})

target_link_libraries(util ${OpenCV_LIBRARIES})
target_link_libraries(util ${XERCESC_LIBRARY})
target_link_libraries(util ${Boost_LIBRARIES})


# Geometry2DTest

set(GEOMETRY2D_TEST_SRC
    test/Geometry2DTest.cpp
)

set(GEOMETRY2D_TEST_LINK_LIBS
    util
    ${OpenCV_LIBRARIES}
    gtest
    gtest_main
)

AddUnitTest(Geometry2DTest "${GEOMETRY2D_TEST_SRC}" "${GEOMETRY2D_TEST_LINK_LIBS}")


# MinEnclosingTriangleFinderTest

set(MIN_ENCLOSING_TRIANGLE_FINDER_TEST_SRC
    test/MinEnclosingTriangleFinderTest.cpp
)

set(MIN_ENCLOSING_TRIANGLE_FINDER_TEST_LINK_LIBS
    util
    ${OpenCV_LIBRARIES}
    gtest
    gtest_main
)

AddUnitTest(MinEnclosingTriangleFinderTest "${MIN_ENCLOSING_TRIANGLE_FINDER_TEST_SRC}" "${MIN_ENCLOSING_TRIANGLE_FINDER_TEST_LINK_LIBS}")


# NumericTest

set(NUMERIC_TEST_SRC
    test/NumericTest.cpp
)

set(NUMERIC_TEST_LINK_LIBS
    util
    gtest
    gtest_main
)

AddUnitTest(NumericTest "${NUMERIC_TEST_SRC}" "${NUMERIC_TEST_LINK_LIBS}")


# StatisticsTest

set(STATISTICS_TEST_SRC
    test/StatisticsTest.cpp
)

set(STATISTICS_TEST_LINK_LIBS
    util
    gtest
    gtest_main
)

AddUnitTest(StatisticsTest "${STATISTICS_TEST_SRC}" "${STATISTICS_TEST_LINK_LIBS}")


# ConsolePrinterSample

set(CONSOLE_PRINTER_SAMPLE_SRC
    sample/ConsolePrinterSample.cpp
)

add_executable(ConsolePrinterSample ${CONSOLE_PRINTER_SAMPLE_SRC})
AddSample(ConsolePrinterSample)

target_link_libraries(ConsolePrinterSample util)


# ExecuteProgramSample

set(EXECUTE_PROGRAM_SAMPLE_SRC
    sample/ExecuteProgramSample.cpp
)

add_executable(ExecuteProgramSample ${EXECUTE_PROGRAM_SAMPLE_SRC})
AddSample(ExecuteProgramSample)

target_link_libraries(ExecuteProgramSample util)


# LineCircleIntersectionSample

set(LINE_CIRCLE_INTERSECTION_SAMPLE_SRC
    sample/LineCircleIntersectionSample.cpp
)

add_executable(LineCircleIntersectionSample ${LINE_CIRCLE_INTERSECTION_SAMPLE_SRC})
AddSample(LineCircleIntersectionSample)

target_link_libraries(LineCircleIntersectionSample util)
target_link_libraries(LineCircleIntersectionSample gtest gtest_main)


# MinEnclosingTriangleFinderSample

set(MIN_ENCLOSING_TRIANGLE_FINDER_SAMPLE_SRC
    sample/MinEnclosingTriangleFinderSample.cpp
)

add_executable(MinEnclosingTriangleFinderSample ${MIN_ENCLOSING_TRIANGLE_FINDER_SAMPLE_SRC})
AddSample(MinEnclosingTriangleFinderSample)

target_link_libraries(MinEnclosingTriangleFinderSample util)
target_link_libraries(MinEnclosingTriangleFinderSample ${OpenCV_LIBRARIES})


# RGBColourGeneratorSample

set(RGB_COLOUR_GENERATOR_SAMPLE_SRC
    sample/RGBColourGeneratorSample.cpp
)

add_executable(RGBColourGeneratorSample ${RGB_COLOUR_GENERATOR_SAMPLE_SRC})
AddSample(RGBColourGeneratorSample)

target_link_libraries(RGBColourGeneratorSample util)


# TangentsFromPointToPolygonSample

set(TANGENTS_FROM_POINT_TO_POLYGON_SAMPLE_SRC
    sample/TangentsFromPointToPolygonSample.cpp
)

add_executable(TangentsFromPointToPolygonSample ${TANGENTS_FROM_POINT_TO_POLYGON_SAMPLE_SRC})
AddSample(TangentsFromPointToPolygonSample)

target_link_libraries(TangentsFromPointToPolygonSample util)


# XmlValidatorSample

set(XML_VALIDATOR_SAMPLE_SRC
    sample/XmlValidatorSample.cpp
)

add_executable(XmlValidatorSample ${XML_VALIDATOR_SAMPLE_SRC})
AddSample(XmlValidatorSample)

target_link_libraries(XmlValidatorSample util)
