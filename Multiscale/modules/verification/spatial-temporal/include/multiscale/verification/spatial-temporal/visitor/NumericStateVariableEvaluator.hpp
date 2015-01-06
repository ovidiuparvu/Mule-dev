#ifndef NUMERICSTATEVARIABLEEVALUATOR_HPP
#define NUMERICSTATEVARIABLEEVALUATOR_HPP

#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"
#include "multiscale/verification/spatial-temporal/visitor/SemanticTypeEvaluator.hpp"


namespace multiscale {

    namespace verification {

        //! Class used to evaluate numeric state variables
        class NumericStateVariableEvaluator {

            public:

                //! Evaluate the provided numeric state variable for the given timepoint
                /*!
                 * \param numericStateVariable  The provided numeric state variable
                 * \param timePoint             The given timepoint
                 * \param typeSemanticsTable    The given type semantics table
                 */
                static double evaluate(const NumericStateVariableAttribute &numericStateVariable,
                                       const TimePoint &timePoint,
                                       const TypeSemanticsTable &typeSemanticsTable) {
                    // Obtain the semantic type
                    std::string semanticType = numericStateVariable.semanticType.get_value_or(
                                                   SemanticTypeAttribute()
                                               ).semanticType;

                    // Validate the semantic type
                    SemanticTypeEvaluator::validate(semanticType, typeSemanticsTable);

                    // Return the value of the numeric state variable
                    return (
                        evaluate(
                            numericStateVariable.stateVariable.name,
                            semanticType,
                            timePoint
                        )
                    );
                }

            private:

                //! Evaluate the provided numeric state variable
                /*!
                 * \param name          The name of the numeric state variable
                 * \param semanticType  The semantic type of the numeric state variable
                 * \param timePoint     The given timepoint
                 */
                static double evaluate(const std::string &name, const std::string &semanticType,
                                       const TimePoint &timePoint) {
                    // Construct the numeric state variable identity considering its name and semantic type
                    NumericStateVariableId numericStateVariableId(
                        name, semanticType
                    );

                    // Return the value of the numeric state variable
                    return (
                        timePoint.getNumericStateVariableValue(numericStateVariableId)
                    );
                }

        };

    };

};


#endif
