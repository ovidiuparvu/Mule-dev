#ifndef NUMERICEVALUATOR_HPP
#define NUMERICEVALUATOR_HPP


#include "multiscale/verification/spatial-temporal/attribute/BinarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/QuaternarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TernarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnarySubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class BinaryNumericNumericAttribute;
        class NumericMeasureAttribute;
        class NumericSpatialAttribute;
        class UnaryNumericNumericAttribute;


        //! Variant for the numeric measure attribute
        typedef boost::variant<
            double,
            multiscale::verification::NumericStateVariableAttribute,
            boost::recursive_wrapper<multiscale::verification::NumericSpatialAttribute>,
            boost::recursive_wrapper<multiscale::verification::UnaryNumericNumericAttribute>,
            boost::recursive_wrapper<multiscale::verification::BinaryNumericNumericAttribute>,
            boost::recursive_wrapper<multiscale::verification::NumericMeasureAttribute>
        > NumericMeasureAttributeType;


        //! Variant for a numeric spatial attribute
        typedef boost::variant<
            UnarySubsetAttribute,
            BinarySubsetAttribute,
            TernarySubsetAttribute,
            QuaternarySubsetAttribute,
            boost::recursive_wrapper<NumericSpatialAttribute>
        > NumericSpatialAttributeType;


        //! Abstract class used for evaluation numeric measures
        class NumericEvaluator {

            public:

                virtual ~NumericEvaluator() {};

                //! Evaluate the truth value of a numeric measure considering the given time point
                /*!
                 * \param timePoint  The given timepoint
                 */
                virtual double evaluate(const TimePoint &timePoint) const = 0;

        };
    };

};

#endif
