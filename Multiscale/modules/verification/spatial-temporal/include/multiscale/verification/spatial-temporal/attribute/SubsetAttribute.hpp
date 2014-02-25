#ifndef SUBSETATTRIBUTE_HPP
#define SUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/FilterSubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class SubsetAttribute;


        //! Variant for a subset attribute
        typedef boost::variant<
            SubsetSpecificAttribute,
            FilterSubsetAttribute,
            boost::recursive_wrapper<SubsetAttribute>
        > SubsetAttributeType;


        //! Class for representing a subset attribute
        class SubsetAttribute : public SubsetEvaluator {

            public:

                SubsetAttributeType subset; /*!< The subset */

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
    multiscale::verification::SubsetAttribute,
    (multiscale::verification::SubsetAttributeType, subset)
)

#endif
