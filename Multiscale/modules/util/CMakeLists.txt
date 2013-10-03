#------------------------------------------------------------
# Include directories
#------------------------------------------------------------

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


#------------------------------------------------------------
# Add library
#------------------------------------------------------------

set(LIB_SRC
    src/Geometry2D.cpp
    src/MinEnclosingTriangleFinder.cpp
    src/NumberIterator.cpp
    src/Numeric.cpp
    src/RGBColourGenerator.cpp
    src/StringManipulator.cpp

    src/iterator/LexicographicNumberIterator.cpp
    src/iterator/StandardNumberIterator.cpp
)

add_library(util SHARED ${LIB_SRC})

target_link_libraries(util ${BOOST_LIBRARIES})
target_link_libraries(util ${OpenCV_LIBRARIES})