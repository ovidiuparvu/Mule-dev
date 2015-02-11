#ifndef SPATIALENTITY_HPP
#define SPATIALENTITY_HPP

#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"

#include <functional>
#include <string>
#include <vector>


namespace multiscale {

    namespace verification {

        //! Class for representing a pseudo-3D spatial entity
        class SpatialEntity {

            protected:

                std::string semanticType;                   /*!< The semantic type of the spatial entity */

                std::vector<double> spatialMeasureValues;   /*!< The vector of spatial measures' values.
                                                                 The i-th spatial measure value in the vector
                                                                 corresponds to the i-th SpatialMeasureType
                                                                 enumeration value */

            public:

                SpatialEntity();
                ~SpatialEntity();

                //! Get the semantic type
                std::string getSemanticType() const;

                //! Set the value of the semantic type
                /*!
                 * \param semanticType The value of the semantic type
                 */
                void setSemanticType(const std::string &semanticType);

                //! Get the value of the given spatial measure
                /*!
                 * \param spatialMeasureType    The spatial measure for which the value is returned
                 */
                double getSpatialMeasureValue(const SpatialMeasureType &spatialMeasureType) const;

                //! Set the value of the given spatial measure
                /*!
                 * \param spatialMeasureType    The spatial measure for which the value is set
                 * \param spatialMeasureValue   The new spatial measure value
                 */
                void setSpatialMeasureValue(const SpatialMeasureType &spatialMeasureType,
                                            double spatialMeasureValue);

                //! Overload the "<" operator for spatial entities
                /*! In this implementation spatial entity se1 is smaller than spatial entity se2 (se1 < se2)
                 * if at least one of the fields in se1 < the corresponding field in se2
                 *
                 * \param rhsSpatialEntity  The spatial entity lying on the right hand side of the comparison operator
                 */
                bool operator<(const SpatialEntity &rhsSpatialEntity);

                //! Overload the "<" operator for spatial entities
                /*! In this implementation spatial entity se1 is smaller than spatial entity se2 (se1 < se2)
                 * if at least one of the fields in se1 < the corresponding field in se2
                 *
                 * \param rhsSpatialEntity  The spatial entity lying on the right hand side of the comparison operator
                 */
                bool operator<(const SpatialEntity &rhsSpatialEntity) const;

                //! Overload the "==" operator for spatial entities
                /*! In this implementation spatial entity se1 is equal to spatial entity se2 (se1 == se2)
                 * if all the fields in se1 == the corresponding fields in se2
                 *
                 * \param rhsSpatialEntity  The spatial entity lying on the right hand side of the comparison operator
                 */
                bool operator==(const SpatialEntity &rhsSpatialEntity);

                //! Overload the "==" operator for spatial entities
                /*! In this implementation spatial entity se1 is equal to spatial entity se2 (se1 == se2)
                 * if all the fields in se1 == the corresponding fields in se2
                 *
                 * \param rhsSpatialEntity  The spatial entity lying on the right hand side of the comparison operator
                 */
                bool operator==(const SpatialEntity &rhsSpatialEntity) const;

                //! Overload the "!=" operator for spatial entities
                /*! In this implementation spatial entity se1 is different from spatial entity se2 (se1 != se2)
                 * if at least one of the fields in se1 != the corresponding field in se2
                 *
                 * \param rhsSpatialEntity  The spatial entity lying on the right hand side of the comparison operator
                 */
                bool operator!=(const SpatialEntity &rhsSpatialEntity);

                //! Overload the "!=" operator for spatial entities
                /*! In this implementation spatial entity se1 is different from spatial entity se2 (se1 != se2)
                 * if at least one of the fields in se1 != the corresponding field in se2
                 *
                 * \param rhsSpatialEntity  The spatial entity lying on the right hand side of the comparison operator
                 */
                bool operator!=(const SpatialEntity &rhsSpatialEntity) const;

                //! Return a string representation of the spatial entity contents
                std::string toString() const;

            private:

                //! Check if the provided value is valid considering the given spatial measure
                /*!
                 * \param spatialMeasureValue   The new spatial measure value
                 * \param spatialMeasureType    The spatial measure for which the value is set
                 */
                void validateSpatialMeasureValue(double spatialMeasureValue,
                                                 const SpatialMeasureType &spatialMeasureType);


                // Constants
                static const std::string OUTPUT_SPATIAL_MEASURE_VALUE_SEPARATOR;

                static const std::string ERR_INVALID_SPATIAL_MEASURE_BEGIN;
                static const std::string ERR_INVALID_SPATIAL_MEASURE_MIDDLE;
                static const std::string ERR_INVALID_SPATIAL_MEASURE_END;

        };

    };

};


#endif
