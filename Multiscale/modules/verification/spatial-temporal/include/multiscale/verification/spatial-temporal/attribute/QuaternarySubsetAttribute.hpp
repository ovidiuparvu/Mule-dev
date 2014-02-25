#ifndef QUATERNARYSUBSETATTRIBUTE_HPP
#define QUATERNARYSUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/QuaternarySubsetMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a quaternary subset attribute
        class QuaternarySubsetAttribute : public NumericEvaluator {

            public:

                QuaternarySubsetMeasureAttribute    quaternarySubsetMeasure;    /*!< The quaternary subset measure */
                SubsetAttributeType                 firstSubset;                /*!< The first considered subset */
                SpatialMeasureAttribute             firstSpatialMeasure;        /*!< The first considered spatial measure */
                SubsetAttributeType                 secondSubset;               /*!< The second considered subset */
                SpatialMeasureAttribute             secondSpatialMeasure;       /*!< The second considered spatial measure */

            public:

                //! Evaluate the truth value of a numeric measure considering the given time point
                /*!
                 * \param timePoint  The given timepoint
                 */
                double evaluate(const TimePoint &timePoint) const override {
                    return 0.0;
                }

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::QuaternarySubsetAttribute,
    (multiscale::verification::QuaternarySubsetMeasureAttribute, quaternarySubsetMeasure)
    (multiscale::verification::SubsetAttributeType, firstSubset)
    (multiscale::verification::SpatialMeasureAttribute, firstSpatialMeasure)
    (multiscale::verification::SubsetAttributeType, secondSubset)
    (multiscale::verification::SpatialMeasureAttribute, secondSpatialMeasure)
)

#endif
