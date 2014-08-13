#ifndef CHANGEMEASUREEVALUATOR_HPP
#define CHANGEMEASUREEVALUATOR_HPP

#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ChangeMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"


namespace multiscale {

    namespace verification {

        //! Class for evaluating change measure expressions
        class ChangeMeasureEvaluator {

            public:

                //! Compute the value of the change measure considering the given numeric measure and time values
                /*!
                 * \param changeMeasureType             The type of the change measure
                 * \param numericMeasureFirstTimepoint  The numeric measure value corresponding to the
                 *                                      initial timepoint
                 * \param numericMeasureSecondTimepoint The numeric measure value corresponding to the
                 *                                      second timepoint
                 * \param timeValueFirstTimepoint       The time value corresponding to the first timepoint
                 * \param timeValueSecondTimepoint      The time value corresponding to the second timepoint
                 */
                static double evaluate(const ChangeMeasureType &changeMeasureType, double numericMeasureFirstTimepoint,
                                       double numericMeasureSecondTimepoint, unsigned long timeValueFirstTimepoint,
                                       unsigned long timeValueSecondTimepoint) {
                    double numericValueChange  = computeNumericMeasureValueChange(
                                                     changeMeasureType, numericMeasureFirstTimepoint,
                                                     numericMeasureSecondTimepoint
                                                 );
                    double timeValueDifference = computeTimeValueDifference(
                                                     timeValueFirstTimepoint,
                                                     timeValueSecondTimepoint
                                                 );

                    return (numericValueChange / timeValueDifference);
                }

            private:

                //! Compute the time value difference considering the given time values
                /*! Time difference = (second timepoint value) - (first timepoint value)
                 *
                 * \param timeValueFirstTimepoint   The time value corresponding to the first timepoint
                 * \param timeValueSecondTimepoint  The time value corresponding to the second timepoint
                 */
                static double computeTimeValueDifference(unsigned long timeValueFirstTimepoint,
                                                         unsigned long timeValueSecondTimepoint) {
                    return static_cast<double>(timeValueSecondTimepoint - timeValueFirstTimepoint);
                }

                //! Compute the numeric measure value change considering the given change measure and numeric values
                /*!
                 * \param changeMeasureType             The type of the change measure
                 * \param numericMeasureFirstTimepoint  The numeric measure value corresponding to the first timepoint
                 * \param numericMeasureSecondTimepoint The numeric measure value corresponding to the second timepoint
                 */
                static double computeNumericMeasureValueChange(const ChangeMeasureType &changeMeasureType,
                                                               unsigned long numericMeasureFirstTimepoint,
                                                               unsigned long numericMeasureSecondTimepoint) {
                    switch(changeMeasureType) {
                        case ChangeMeasureType::Derivative:
                            return (numericMeasureSecondTimepoint - numericMeasureFirstTimepoint);
                            break;

                        case ChangeMeasureType::Ratio:
                            return (numericMeasureSecondTimepoint / numericMeasureFirstTimepoint);
                            break;

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return 0.0;
                }

        };

    };

};


#endif
