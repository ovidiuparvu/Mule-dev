#ifndef SPATIALMEASURETYPE_HPP
#define SPATIALMEASURETYPE_HPP

/******************************************************************************
 *
 * WARNING! AUTO-GENERATED FILE.
 *
 * PLEASE DO NOT UPDATE THIS FILE MANUALLY. 
 * USE THE PYTHON GENERATOR SCRIPTS FOR ANY MODIFICATIONS.
 *
 *****************************************************************************/
 
 
namespace multiscale {

    namespace verification {

        //! Enumeration for representing the types of spatial measures
        enum class SpatialMeasureType : unsigned int {
            Clusteredness                     = 0,    /*!< The clusteredness of a spatial entity */
            Density                              ,    /*!< The density of a spatial entity */
            Area                                 ,    /*!< The area of a spatial entity */
            Perimeter                            ,    /*!< The perimeter of a spatial entity */
            DistanceFromOrigin                   ,    /*!< The distance of a spatial entity from origin */
            Angle                                ,    /*!< The angle */
            TriangleMeasure                      ,    /*!< The measure indicating how triangular is the shape of the spatial entity */
            RectangleMeasure                     ,    /*!< The measure indicating how rectangular is the shape of the spatial entity */
            CircleMeasure                        ,    /*!< The measure indicating how circular is the shape of the spatial entity */
            CentroidX                            ,    /*!< The x coordinate of the spatial entity centroid */
            CentroidY                            ,    /*!< The y coordinate of the spatial entity centroid */
            NrOfSpatialMeasureTypeEntries             /*!< Enumeration type used to store the number of
                                                           elements in the enumeration. Always leave it last! */
        };

    };

};


#endif