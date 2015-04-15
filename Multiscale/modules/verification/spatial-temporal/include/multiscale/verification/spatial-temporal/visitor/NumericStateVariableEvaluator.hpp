#ifndef NUMERICSTATEVARIABLEEVALUATOR_HPP
#define NUMERICSTATEVARIABLEEVALUATOR_HPP

#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"
#include "multiscale/verification/spatial-temporal/visitor/ScaleAndSubsystemEvaluator.hpp"


namespace multiscale {

    namespace verification {

        //! Class used to evaluate numeric state variables
        class NumericStateVariableEvaluator {

            public:

                //! Evaluate the provided numeric state variable for the given timepoint
                /*!
                 * \param numericStateVariable          The provided numeric state variable
                 * \param timePoint                     The given timepoint
                 * \param multiscaleArchitectureGraph   The given multiscale architecture graph
                 */
                static double evaluate(const NumericStateVariableAttribute &numericStateVariable,
                                       const TimePoint &timePoint,
                                       const MultiscaleArchitectureGraph &multiscaleArchitectureGraph) {
                    // Obtain the scale and subsystem
                    std::string scaleAndSubsystem = numericStateVariable.scaleAndSubsystem.get_value_or(
                                                        ScaleAndSubsystemAttribute()
                                                    ).scaleAndSubsystem;

                    // Validate the scale and subsystem
                    ScaleAndSubsystemEvaluator::validateScaleAndSubsystem(
                        scaleAndSubsystem,
                        multiscaleArchitectureGraph
                    );

                    // Return the value of the numeric state variable
                    return (
                        evaluate(
                            numericStateVariable.stateVariable.name,
                            scaleAndSubsystem,
                            timePoint
                        )
                    );
                }

            private:

                //! Evaluate the provided numeric state variable
                /*!
                 * \param name              The name of the numeric state variable
                 * \param scaleAndSubsystem The scale and subsystem associated with the numeric state variable
                 * \param timePoint         The given timepoint
                 */
                static double evaluate(const std::string &name, const std::string &scaleAndSubsystem,
                                       const TimePoint &timePoint) {
                    // Construct the numeric state variable identity considering its name, and scale and subsystem
                    NumericStateVariableId numericStateVariableId(
                        name, scaleAndSubsystem
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
