#ifndef SPATIALMEASUREATTRIBUTE_HPP
#define SPATIALMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


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

        //! An std::size_t constant which stores the number of spatial measure type entries
        static const std::size_t
        NR_SPATIAL_MEASURE_TYPES = static_cast<std::size_t>(SpatialMeasureType::NrOfSpatialMeasureTypeEntries);

        namespace spatialmeasure {

            //! Check if the given spatial measure type is valid
            /*!
             * \param spatialMeasureType    The given spatial measure type
             */
            void validateSpatialMeasureType(const SpatialMeasureType &spatialMeasureType);

            //! Check if the given spatial measure type index is valid
            /*!
             * \param spatialMeasureTypeIndex   The given spatial measure type index
             */
            void validateSpatialMeasureTypeIndex(const std::size_t &spatialMeasureTypeIndex);

            //! Compute the index of the spatial measure type
            /*!
             * \param spatialMeasureType The given spatial measure type
             */
            size_t computeSpatialMeasureTypeIndex(const SpatialMeasureType &spatialMeasureType);

            //! Compute the spatial measure type from the given index
            /*!
             * \param spatialMeasureTypeIndex    The given spatial measure type index
             */
            SpatialMeasureType computeSpatialMeasureType(const std::size_t &spatialMeasureTypeIndex);

            //! Get the minimum valid value for the given spatial measure type
            /*!
             * \param spatialMeasureType    The given spatial measure type
             */
            double getMinValidSpatialMeasureValue(const SpatialMeasureType &spatialMeasureType);

            //! Get the maximum valid value for the given spatial measure type
            /*!
             * \param spatialMeasureType    The given spatial measure type
             */
            double getMaxValidSpatialMeasureValue(const SpatialMeasureType &spatialMeasureType);

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

                SpatialMeasureType spatialMeasureType;    /*!< The spatial measure type */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SpatialMeasureAttribute,
    (multiscale::verification::SpatialMeasureType, spatialMeasureType)
)

#endif
