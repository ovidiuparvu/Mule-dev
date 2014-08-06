#ifndef SPATIALMEASURETYPE_HPP
#define SPATIALMEASURETYPE_HPP

namespace multiscale {

    namespace verification {

        //! Enumeration for representing the types of spatial measures
        enum class SpatialMeasureType : unsigned int {
            Clusteredness                   = 0,    /*!< The clusteredness of the spatial entity */
            Density                            ,    /*!< The density of the spatial entity */
            Area                               ,    /*!< The area of the spatial entity */
            Perimeter                          ,    /*!< The perimeter of the spatial entity */
            DistanceFromOrigin                 ,    /*!< The distance of the spatial entity from the origin (centre of the discretised space) */
            Angle                              ,    /*!< The angle determined by the spatial entity wrt the origin (centre of the discretised space) in degrees */
            TriangleMeasure                    ,    /*!< The measure indicating how triangular is the shape of the spatial entity */
            RectangleMeasure                   ,    /*!< The measure indicating how rectangular is the shape of the spatial entity */
            CircleMeasure                      ,    /*!< The measure indicating how circular is the shape of the spatial entity */
            CentroidX                          ,    /*!< The x coordinate of the centroid of the spatial entity */
            CentroidY                          ,    /*!< The y coordinate of the centroid of the spatial entity */
            NrOfSpatialMeasureTypeEntries           /*!< Enumeration type used to store the number of
                                                         elements in the enumeration. Always leave it last! */
        };

    };

};

#endif
