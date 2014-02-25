#ifndef SPATIALMEASUREATTRIBUTE_HPP
#define SPATIALMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing the types of spatial measures
        enum class SpatialMeasureType : int {
            Clusteredness       = 1,    /*!< The clusteredness of the spatial entity */
            Density             = 2,    /*!< The density of the spatial entity */
            Area                = 3,    /*!< The area of the spatial entity */
            Perimeter           = 4,    /*!< The perimeter of the spatial entity */
            DistanceFromOrigin  = 5,    /*!< The distance of the spatial entity from the origin (centre of the discretised space) */
            Angle               = 6,    /*!< The angle determined by the spatial entity wrt the origin (centre of the discretised space) */
            TriangleMeasure     = 7,    /*!< The measure indicating how triangular is the shape of the spatial entity */
            RectangleMeasure    = 8,    /*!< The measure indicating how rectangular is the shape of the spatial entity */
            CircleMeasure       = 9,    /*!< The measure indicating how circular is the shape of the spatial entity */
            CentroidX           = 10,   /*!< The x coordinate of the centroid of the spatial entity */
            CentroidY           = 11    /*!< The y coordinate of the centroid of the spatial entity */
        };


        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                   Output stream
         * \param spatialMeasureType    The spatial measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out, const SpatialMeasureType &spatialMeasureType);


        //! Class for representing a spatial measure attribute
        class SpatialMeasureAttribute {

            public:

                SpatialMeasureType spatialMeasure;    /*!< The spatial measure */

            public:

                //! Return the spatial measure type
                SpatialMeasureType evaluate() const;
        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SpatialMeasureAttribute,
    (multiscale::verification::SpatialMeasureType, spatialMeasure)
)

#endif
