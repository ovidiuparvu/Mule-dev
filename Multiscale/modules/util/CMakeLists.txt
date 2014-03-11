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
    src/Geometry2D.cpp
    src/MinEnclosingTriangleFinder.cpp
    src/NumberIterator.cpp
    src/Numeric.cpp
    src/RGBColourGenerator.cpp
    src/StringManipulator.cpp
    src/XmlValidator.cpp

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

add_executable(Geometry2DTest ${GEOMETRY2D_TEST_SRC})
AddUnitTest(Geometry2DTest)

target_link_libraries(Geometry2DTest util)
target_link_libraries(Geometry2DTest ${OpenCV_LIBRARIES})
target_link_libraries(Geometry2DTest gtest gtest_main)


# LineCircleIntersectionSample

set(LINE_CIRCLE_INTERSECTION_SAMPLE_SRC
    sample/LineCircleIntersectionSample.cpp
)

add_executable(LineCircleIntersectionSample ${LINE_CIRCLE_INTERSECTION_SAMPLE_SRC})
AddSample(LineCircleIntersectionSample)

target_link_libraries(LineCircleIntersectionSample util)
target_link_libraries(LineCircleIntersectionSample gtest gtest_main)


# MinEnclosingTriangleFinderTest

set(MIN_ENCLOSING_TRIANGLE_FINDER_TEST_SRC
    test/MinEnclosingTriangleFinderTest.cpp
)

add_executable(MinEnclosingTriangleFinderTest ${MIN_ENCLOSING_TRIANGLE_FINDER_TEST_SRC})
AddUnitTest(MinEnclosingTriangleFinderTest)

target_link_libraries(MinEnclosingTriangleFinderTest util)
target_link_libraries(MinEnclosingTriangleFinderTest ${OpenCV_LIBRARIES})
target_link_libraries(MinEnclosingTriangleFinderTest gtest gtest_main)


# NumericTest

set(NUMERIC_TEST_SRC
    test/NumericTest.cpp
)

add_executable(NumericTest ${NUMERIC_TEST_SRC})
AddUnitTest(NumericTest)

target_link_libraries(NumericTest util)
target_link_libraries(NumericTest gtest gtest_main)


# MinEnclosingTriangleFinderSample

set(MIN_ENCLOSING_TRIANGLE_FINDER_SAMPLE_SRC
    sample/MinEnclosingTriangleFinderSample.cpp
)

add_executable(MinEnclosingTriangleFinderSample ${MIN_ENCLOSING_TRIANGLE_FINDER_SAMPLE_SRC})
AddSample(MinEnclosingTriangleFinderSample)

target_link_libraries(MinEnclosingTriangleFinderSample util)
target_link_libraries(MinEnclosingTriangleFinderSample ${OpenCV_LIBRARIES})
target_link_libraries(MinEnclosingTriangleFinderSample gtest gtest_main)


# RGBColourGeneratorSample

set(RGB_COLOUR_GENERATOR_SAMPLE_SRC
    sample/RGBColourGeneratorSample.cpp
)

add_executable(RGBColourGeneratorSample ${RGB_COLOUR_GENERATOR_SAMPLE_SRC})
AddSample(RGBColourGeneratorSample)

target_link_libraries(RGBColourGeneratorSample util)
target_link_libraries(RGBColourGeneratorSample gtest gtest_main)