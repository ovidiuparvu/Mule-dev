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
                 *                                                      initial timepoint
                 * \param temporalNumericMeasureCollectionSecondValue   The temporal numeric measure collection value
                 *                                                      corresponding to the trace starting from the
                 *                                                      timepoint succeeding the initial timepoint
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
                 * \param temporalNumericMeasureFirstTimepoint  The temporal numeric measure value corresponding to the
                 *                                              trace starting from the initial timepoint
                 * \param temporalNumericMeasureSecondTimepoint The temporal numeric measure value corresponding to the
                 *                                              trace starting from the second timepoint
                 * \param timeValueFirstTimepoint               The time value corresponding to the first timepoint
                 * \param timeValueSecondTimepoint              The time value corresponding to the second timepoint
                 */
                static double evaluate(const ChangeMeasureType &changeMeasureType,
                                       double temporalNumericMeasureFirstTimepoint,
                                       double temporalNumericMeasureSecondTimepoint,
                                       unsigned long timeValueFirstTimepoint,
                                       unsigned long timeValueSecondTimepoint) {
                    double temporalNumericValueChange  = computeNumericMeasureValueChange(
                                                             changeMeasureType,
                                                             temporalNumericMeasureFirstTimepoint,
                                                             temporalNumericMeasureSecondTimepoint
                                                         );
                    double timeValueDifference = computeTimeValueDifference(
                                                     timeValueFirstTimepoint,
                                                     timeValueSecondTimepoint
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
                 * \param changeMeasureType                     The type of the change measure
                 * \param temporalNumericMeasureFirstTimepoint  The temporal numeric measure value corresponding to the
                 *                                              trace starting from the initial timepoint
                 * \param temporalNumericMeasureSecondTimepoint The temporal numeric measure value corresponding to the
                 *                                              trace starting from the second timepoint
                 */
                static double computeNumericMeasureValueChange(const ChangeMeasureType &changeMeasureType,
                                                               double temporalNumericMeasureFirstTimepoint,
                                                               double temporalNumericMeasureSecondTimepoint) {
                    switch(changeMeasureType) {
                        case ChangeMeasureType::Derivative:
                            return (temporalNumericMeasureSecondTimepoint - temporalNumericMeasureFirstTimepoint);
                            break;

                        case ChangeMeasureType::Ratio:
                            return (
                                Numeric::division(
                                    temporalNumericMeasureSecondTimepoint,
                                    temporalNumericMeasureFirstTimepoint
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
