#ifndef FILTERSUBSETATTRIBUTE_HPP
#define FILTERSUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a filter subset attribute
        class FilterSubsetAttribute : public SubsetEvaluator {

            public:

                SubsetSpecificAttribute     subsetSpecific;    /*!< The specific subset to consider */
                ConstraintAttributeType     constraint;        /*!< The constraint */

            public:

                //! Compute a subset of spatial entities for the given timepoint
                /*!
                 * \param timePoint The given timepoint
                 */
                TimePoint evaluate(const TimePoint timePoint) const override {
                    return timePoint;
                }

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::FilterSubsetAttribute,
    (multiscale::verification::SubsetSpecificAttribute, subsetSpecific)
    (multiscale::verification::ConstraintAttributeType, constraint)
)

#endif
