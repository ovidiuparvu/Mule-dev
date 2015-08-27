#ifndef CHANGEMEASUREEVALUATOR_HPP
#define CHANGEMEASUREEVALUATOR_HPP

#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ChangeMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"


namespace multiscale {

    namespace verification {

        //! Class for evaluating change measure expressions
        class ChangeMeasureEvaluator {

            public:

                //! Compute the change measure value considering temporal numeric measure collection and time values
                /*!
                 * \param changeMeasureType                             The type of the change measure
                 * \param temporalNumericMeasureCollectionFirstValue    The temporal numeric measure collection value
                 *                                                      corresponding to the trace starting from the
                 *                                                      initial time point
                 * \param temporalNumericMeasureCollectionSecondValue   The temporal numeric measure collection value
                 *                                                      corresponding to the trace starting from the
                 *                                                      time point succeeding the initial time point
                 */
                static double evaluate(const ChangeMeasureType &changeMeasureType,
                                       double temporalNumericMeasureCollectionFirstValue,
                                       double temporalNumericMeasureCollectionSecondValue) {
                    return computeNumericMeasureValueChange(
                         changeMeasureType,
                         temporalNumericMeasureCollectionFirstValue,
                         temporalNumericMeasureCollectionSecondValue
                     );
                }

                //! Compute the change measure value considering the given temporal numeric measure and time values
                /*!
                 * \param changeMeasureType                     The type of the change measure
                 * \param temporalNumericMeasureFirstTimePoint  The temporal numeric measure value corresponding to the
                 *                                              trace starting from the initial time point
                 * \param temporalNumericMeasureSecondTimePoint The temporal numeric measure value corresponding to the
                 *                                              trace starting from the second time point
                 * \param timeValueFirstTimePoint               The time value corresponding to the first time point
                 * \param timeValueSecondTimePoint              The time value corresponding to the second time point
                 */
                static double evaluate(const ChangeMeasureType &changeMeasureType,
                                       double temporalNumericMeasureFirstTimePoint,
                                       double temporalNumericMeasureSecondTimePoint,
                                       double timeValueFirstTimePoint,
                                       double timeValueSecondTimePoint) {
                    double temporalNumericValueChange
                        = computeNumericMeasureValueChange(
                              changeMeasureType,
                              temporalNumericMeasureFirstTimePoint,
                              temporalNumericMeasureSecondTimePoint
                          );
                    double timeValueDifference
                        = computeTimeValueDifference(
                              timeValueFirstTimePoint,
                              timeValueSecondTimePoint
                          );

                    return (
                        Numeric::division(
                            temporalNumericValueChange,
                            timeValueDifference
                        )
                    );
                }

            private:

                //! Compute the time value difference considering the given time values
                /*! Time difference = (second time point value) - (first time point value)
                 *
                 * \param timeValueFirstTimePoint   The time value corresponding to the first time point
                 * \param timeValueSecondTimePoint  The time value corresponding to the second time point
                 */
                static double computeTimeValueDifference(double timeValueFirstTimePoint,
                                                         double timeValueSecondTimePoint) {
                    return (timeValueSecondTimePoint - timeValueFirstTimePoint);
                }

                //! Compute the numeric measure value change considering the given change measure and numeric values
                /*!
                 * \param changeMeasureType                     The type of the change measure
                 * \param temporalNumericMeasureFirstTimePoint  The temporal numeric measure value corresponding to the
                 *                                              trace starting from the initial time point
                 * \param temporalNumericMeasureSecondTimePoint The temporal numeric measure value corresponding to the
                 *                                              trace starting from the second time point
                 */
                static double computeNumericMeasureValueChange(const ChangeMeasureType &changeMeasureType,
                                                               double temporalNumericMeasureFirstTimePoint,
                                                               double temporalNumericMeasureSecondTimePoint) {
                    switch(changeMeasureType) {
                        case ChangeMeasureType::Derivative:
                            return (temporalNumericMeasureSecondTimePoint - temporalNumericMeasureFirstTimePoint);
                            break;

                        case ChangeMeasureType::Ratio:
                            return (
                                Numeric::division(
                                    temporalNumericMeasureSecondTimePoint,
                                    temporalNumericMeasureFirstTimePoint
                                )
                            );
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
