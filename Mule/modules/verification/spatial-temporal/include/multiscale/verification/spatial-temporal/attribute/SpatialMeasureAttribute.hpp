#ifndef SPATIALMEASUREATTRIBUTE_HPP
#define SPATIALMEASUREATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureType.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! An size_t constant which stores the number of spatial measure type entries
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

            //! Get the string representation of the given spatial measure type
            /*!
             * \param spatialMeasureType    The given spatial measure type
             */
            std::string toString(const SpatialMeasureType &spatialMeasureType);

            //! Get the string representation corresponding to the the given spatial measure type index
            /*!
             * \param spatialMeasureTypeIndex    The given spatial measure type index
             */
            std::string toString(const std::size_t &spatialMeasureTypeIndex);

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
