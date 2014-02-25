#ifndef NUMERICSTATEVARIABLEATTRIBUTE_HPP
#define NUMERICSTATEVARIABLEATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/StateVariableAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a numeric state variable attribute
        class NumericStateVariableAttribute : public NumericEvaluator {

            public:

                StateVariableAttribute stateVariable;    /*!< The state variable */

            public:

                //! Evaluate the truth value of a numeric measure considering the given time point
                /*!
                 * \param timePoint  The given timepoint
                 */
                double evaluate(const TimePoint &timePoint) const override {
                    std::string name = stateVariable.evaluate();

                    return timePoint.getNumericStateVariable(name);
                }

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericStateVariableAttribute,
    (multiscale::verification::StateVariableAttribute, stateVariable)
)

#endif
