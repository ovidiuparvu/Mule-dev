#ifndef NUMERICMEASURECOLLECTIONVISITOR_HPP
#define NUMERICMEASURECOLLECTIONVISITOR_HPP

#include "multiscale/verification/spatial-temporal/visitor/ChangeMeasureEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/TimeseriesComponentVisitor.hpp"

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        //! Class for evaluating numeric measure collections
        class NumericMeasureCollectionVisitor : public boost::static_visitor<std::vector<double>> {

            private:

                const SpatialTemporalTrace &trace;  /*!< The considered spatial temporal trace */


            public:

                NumericMeasureCollectionVisitor(const SpatialTemporalTrace &trace) : trace(trace) {}

                //! Overloading the "()" operator for the TemporalNumericCollectionAttribute alternative
                /*!
                 * \param temporalNumericCollection The temporal numeric collection
                 */
                std::vector<double>
                operator()(const TemporalNumericCollectionAttribute &temporalNumericCollection) const;

                //! Overloading the "()" operator for the SpatialMeasureCollectionAttribute alternative
                /*!
                 * \param spatialMeasureCollection  The spatial measure collection
                 */
                std::vector<double>
                operator()(const SpatialMeasureCollectionAttribute &spatialMeasureCollection) const;

                //! Overloading the "()" operator for the TemporalNumericMeasureCollectionAttribute alternative
                /*!
                 * \param temporalNumericMeasureCollection The temporal numeric measure collection
                 */
                std::vector<double>
                operator()(const TemporalNumericMeasureCollectionAttribute &temporalNumericMeasureCollection) const {
                    return evaluateTemporalNumericMeasureCollection(
                        trace,
                        temporalNumericMeasureCollection.startTimepoint,
                        temporalNumericMeasureCollection.endTimepoint,
                        temporalNumericMeasureCollection.numericMeasure
                    );
                }

                //! Overloading the "()" operator for the ChangeTemporalNumericCollectionAttribute alternative
                /*!
                 * \param changeTemporalNumericCollection The change temporal numeric collection
                 */
                std::vector<double>
                operator()(const ChangeTemporalNumericCollectionAttribute &changeTemporalNumericCollection) const;

                //! Overloading the "()" operator for the TimeseriesTimeseriesComponent alternative
                /*!
                 * \param timeseriesTimeseriesComponent The timeseries measure - timeseries component
                 */
                std::vector<double>
                operator()(const TimeseriesTimeseriesComponentAttribute &timeseriesTimeseriesComponent) const {
                    std::vector<double> values = evaluateTemporalNumericMeasureCollection(
                        trace,
                        timeseriesTimeseriesComponent.temporalNumericMeasureCollection.startTimepoint,
                        timeseriesTimeseriesComponent.temporalNumericMeasureCollection.endTimepoint,
                        timeseriesTimeseriesComponent.temporalNumericMeasureCollection.numericMeasure
                    );

                    std::vector<double> timepoints = evaluateTemporalNumericMeasureCollectionTimepoints(
                        trace,
                        timeseriesTimeseriesComponent.temporalNumericMeasureCollection.startTimepoint,
                        timeseriesTimeseriesComponent.temporalNumericMeasureCollection.endTimepoint
                    );

                    std::vector<std::size_t> indices = evaluateTimeseriesComponent(
                        values,
                        timeseriesTimeseriesComponent.timeseriesComponent
                    );

                    return evaluateTimeseriesTimeseriesComponent(
                        timeseriesTimeseriesComponent.timeseriesMeasure.timeseriesMeasure,
                        values, timepoints, indices
                    );
                }

                //! Overloading the "()" operator for the HomogeneousHomogeneousTimeseriesAttribute alternative
                /*!
                 * \param homogeneousHomogeneousTimeseries The homogeneous homogeneous timeseries component
                 */
                std::vector<double>
                operator()(const HomogeneousHomogeneousTimeseriesAttribute &homogeneousHomogeneousTimeseries) const {
                    std::vector<double> values = evaluateTemporalNumericMeasureCollection(
                        trace,
                        homogeneousHomogeneousTimeseries.temporalNumericMeasureCollection.startTimepoint,
                        homogeneousHomogeneousTimeseries.temporalNumericMeasureCollection.endTimepoint,
                        homogeneousHomogeneousTimeseries.temporalNumericMeasureCollection.numericMeasure
                    );

                    std::vector<double> timepoints = evaluateTemporalNumericMeasureCollectionTimepoints(
                        trace,
                        homogeneousHomogeneousTimeseries.temporalNumericMeasureCollection.startTimepoint,
                        homogeneousHomogeneousTimeseries.temporalNumericMeasureCollection.endTimepoint
                    );

                    std::vector<std::size_t> indices = TimeseriesComponentEvaluator::evaluate(
                        homogeneousHomogeneousTimeseries.homogeneousTimeseriesComponent,
                        values
                    );

                    return evaluateHomogeneousHomogeneousTimeseries(
                        homogeneousHomogeneousTimeseries.homogeneousTimeseriesMeasure.homogeneousTimeseriesMeasure,
                        values, timepoints, indices
                    );
                }

            private:

                //! Evaluate the temporal numeric measure collection considering the given spatio-temporal trace
                /*!
                 * \param trace             The considered spatio-temporal trace
                 * \param startTimepoint    The considered start timepoint value
                 * \param endTimepoint      The considered end timepoint value
                 * \param numericMeasure    The numeric measure to be evaluated
                 */
                std::vector<double>
                evaluateTemporalNumericMeasureCollection(const SpatialTemporalTrace &trace,
                                                         unsigned long startTimepoint,
                                                         unsigned long endTimepoint,
                                                         const NumericMeasureType &numericMeasure) const;

                //! Compute the collection of timepoints considering the given trace, and start and end timepoints
                /*!
                 * \param trace             The considered spatio-temporal trace
                 * \param startTimepoint    The considered start timepoint value
                 * \param endTimepoint      The considered end timepoint value
                 */
                std::vector<double>
                evaluateTemporalNumericMeasureCollectionTimepoints(const SpatialTemporalTrace &trace,
                                                                   unsigned long startTimepoint,
                                                                   unsigned long endTimepoint) const {
                    std::vector<double> timePoints;

                    SpatialTemporalTrace traceCopy(trace);

                    // Compute the timepoints values
                    for (unsigned long i = startTimepoint; i <= endTimepoint; i = traceCopy.nextTimePointValue()) {
                        traceCopy.setSubTrace(i);

                        // Add timepoint to collection
                        timePoints.push_back(
                            static_cast<double>(i)
                        );
                    }

                    return timePoints;
                }

                //! Evaluate the temporal numeric collection values considering the given change measure
                /*!
                 * \param changeMeasure                     The given change measure
                 * \param temporalNumericCollectionValues   The values in the temporal numeric collection
                 */
                std::vector<double>
                evaluateChangeTemporalNumericCollection(const ChangeMeasureAttribute &changeMeasure,
                                                        const std::vector<double>
                                                        &temporalNumericCollectionValues) const {
                    std::vector<double> changeMeasureValues;

                    // Stop at the last but one element index because both (index) and
                    // (index + 1) are considered below
                    std::size_t temporalNumericCollectionEndIndex
                        = (temporalNumericCollectionValues.size() > 0)
                              ? (temporalNumericCollectionValues.size() - 1)
                              : 0;

                    // Compute the change measure values
                    for (std::size_t i = 0; i < temporalNumericCollectionEndIndex; i++) {
                        changeMeasureValues.push_back(
                            ChangeMeasureEvaluator::evaluate(
                                changeMeasure.changeMeasureType,
                                temporalNumericCollectionValues[i],
                                temporalNumericCollectionValues[i + 1]
                            )
                        );
                    }

                    return changeMeasureValues;
                }

                //! Evaluate the timeseries component considering the given collection of values
                /*!
                 * \param values                The collection of real values for which timeseries components
                 *                              are computed
                 * \param timeseriesComponent   The considered specific timeseries component type
                 */
                std::vector<std::size_t>
                evaluateTimeseriesComponent(const std::vector<double> &values,
                                            const TimeseriesComponentAttribute &timeseriesComponent) const {
                    return boost::apply_visitor(
                        TimeseriesComponentVisitor(values),
                        timeseriesComponent.timeseriesComponent
                    );
                }

                //! Evaluate the given timeseries timeseries component
                /*! Provided are the temporal numeric measure collection values, the corresponding timepoints
                 *  and both start and end timepoints for timeseries components.
                 *
                 * \param timeseriesMeasureType The considered specific timeseries measure type
                 * \param values                The temporal numeric measure collection values
                 * \param timePoints            The collection of timepoints corresponding to the temporal numeric
                 *                              collection values
                 * \param indices               The indices pointing to the starting and ending positions of timeseries
                 *                              components in the collection of values/timepoints
                 */
                std::vector<double>
                evaluateTimeseriesTimeseriesComponent(const TimeseriesMeasureType &timeseriesMeasureType,
                                                      const std::vector<double> &values,
                                                      const std::vector<double> &timePoints,
                                                      const std::vector<std::size_t> &indices) const {
                    switch(timeseriesMeasureType) {
                        case TimeseriesMeasureType::EnteringTime:
                            return subCollection(
                                timePoints,
                                indicesSubCollection(indices, 0, 2) // Consider only the start/entering indices
                            );
                            break;

                        case TimeseriesMeasureType::EnteringValue:
                            return subCollection(
                                values,
                                indicesSubCollection(indices, 0, 2) // Consider only the start/entering indices
                            );
                            break;

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return std::vector<double>();
                }

                //! Compute the collection of sub-indices from the given collection of indices
                /*!
                 * \param indices       The collection of start and end indices
                 * \param startPosition The first considered position from the indices collection
                 * \param step          The ("number of positions" + 1) between two consecutive elements
                 *                      from the initial indices collection which are included
                 *                      in the sub-collection
                 */
                std::vector<std::size_t>
                indicesSubCollection(const std::vector<std::size_t> &indices, std::size_t startPosition,
                                     std::size_t step) const {
                    std::vector<std::size_t> indicesSubCollection;

                    std::size_t nrOfIndices = indices.size();

                    // Add indices to sub-collection
                    for (std::size_t i = startPosition; i < nrOfIndices; i += step) {
                        indicesSubCollection.push_back(indices[i]);
                    }

                    return indicesSubCollection;
                }

                //! Construct sub-collection considering the given indices
                /*! Only valid indices will be considered. If an invalid index is encountered an exception is thrown.
                 *
                 *
                 * \param initialCollection     The initial collection
                 * \param indices               The indices pointing to element positions from initial collection
                 *                              which will be included in sub-collection
                 */
                template <typename T>
                std::vector<T>
                subCollection(const std::vector<T> &initialCollection,
                              const std::vector<std::size_t> &indices) const {
                    std::vector<T> subCollection;

                    // Add elements to subcollection
                    for (std::size_t index : indices) {
                        subCollection.push_back(
                            initialCollection.at(index)
                        );
                    }

                    return subCollection;
                }

                //! Evaluate the given homogenous homogeneous timeseries
                /*! Provided are the temporal numeric measure collection values, the corresponding timepoints
                 *  and both start and end timepoints for timeseries components.
                 *
                 * \param homogeneousTimeseriesMeasureType  The considered specific homogeneous timeseries measure type
                 * \param values                            The temporal numeric measure collection values
                 * \param timePoints                        The collection of timepoints corresponding to the temporal
                 *                                          numeric collection values
                 * \param indices                           The indices pointing to the starting and ending positions
                 *                                          of timeseries components in the collection of
                 *                                          values/timepoints
                 */
                std::vector<double>
                evaluateHomogeneousHomogeneousTimeseries(const HomogeneousTimeseriesMeasureType
                                                         &homogeneousTimeseriesMeasureType,
                                                         const std::vector<double> &values,
                                                         const std::vector<double> &timePoints,
                                                         const std::vector<std::size_t> &indices) const {
                    switch(homogeneousTimeseriesMeasureType) {
                        case HomogeneousTimeseriesMeasureType::TimeSpan:
                            return computeHomogeneousComponentTimeSpans(
                                timePoints,
                                indices
                            );
                            break;

                        case HomogeneousTimeseriesMeasureType::Values:
                            return computeHomogeneousComponentValues(
                                values,
                                indices
                            );
                            break;

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return std::vector<double>();
                }

                //! Compute the time spans from a timepoints collection using the given start and end timepoint indices
                /*! The provided indices collection contains (start, end) pairs where start/end denotes the
                 *  starting/ending position of a time span in the initial collection which should be
                 *  included in the resulting collection.
                 *
                 * \param timePoints    The given collection of timePoints
                 * \param indices       The collection of both start and end indices pointing to the start and end
                 *                      positions in the values collection
                 */
                std::vector<double>
                computeHomogeneousComponentTimeSpans(const std::vector<double> &timePoints,
                                                     const std::vector<std::size_t> &indices) const {
                    std::vector<double> homogeneousComponentTimeSpans;

                    // Stop at the last but one element index because both (index) and
                    // (index + 1) are considered below
                    std::size_t stopIndex = (indices.size() > 0) ? (indices.size() - 1)
                                                                  : 0;

                    for (std::size_t i = 0; i < stopIndex; i += 2) {
                        homogeneousComponentTimeSpans.push_back(
                            timePoints[indices.at(i + 1)] - timePoints[indices.at(i)]
                        );
                    }

                    return homogeneousComponentTimeSpans;
                }

                //! Compute the values subsequence from a collection considering the given start and end indices
                /*! The provided indices collection contains (start, end) pairs where start/end denotes the
                 *  starting/ending position of a sequence of values in the initial collection which should be
                 *  included in the resulting collection.
                 *
                 * \param values    The given collection of values
                 * \param indices   The collection of both start and end indices pointing to the start and end
                 *                  positions in the values collection
                 */
                std::vector<double>
                computeHomogeneousComponentValues(const std::vector<double> &values,
                                                  const std::vector<std::size_t> &indices) const {
                    std::vector<double> homogeneousComponentValues;

                    // Stop at the last but one element index because both (index) and
                    // (index + 1) are considered below
                    std::size_t stopIndex = (indices.size() > 0) ? (indices.size() - 1)
                                                                 : 0;

                    for (std::size_t i = 0; i < stopIndex; i += 2) {
                        for (std::size_t j = indices.at(i); j <= indices.at(i + 1); j++) {
                            homogeneousComponentValues.push_back(values.at(j));
                        }
                    }

                    return homogeneousComponentValues;
                }

        };

    };

};


// Includes added after class declaration to avoid include circular dependency errors

#include "multiscale/verification/spatial-temporal/visitor/NumericMeasureCollectionEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/NumericVisitor.hpp"


// Methods which depend on the immediately above included classes

inline std::vector<double>
multiscale::verification::NumericMeasureCollectionVisitor::operator()(
    const TemporalNumericCollectionAttribute &temporalNumericCollection
) const {
    return NumericMeasureCollectionEvaluator::evaluateTemporalNumericCollection(
        trace,
        temporalNumericCollection
    );
}

inline std::vector<double>
multiscale::verification::NumericMeasureCollectionVisitor::operator()(
    const SpatialMeasureCollectionAttribute &spatialMeasureCollection
) const {
    return NumericMeasureCollectionEvaluator::evaluateSpatialMeasureCollection(
        trace.getTimePoint(0),
        spatialMeasureCollection
    );
}

inline std::vector<double>
multiscale::verification::NumericMeasureCollectionVisitor::operator()(
    const ChangeTemporalNumericCollectionAttribute &changeTemporalNumericCollection
) const {
    std::vector<double> temporalNumericCollectionValues
        = NumericMeasureCollectionEvaluator::evaluateTemporalNumericCollection(
              trace,
              changeTemporalNumericCollection.temporalNumericCollection
          );

    return evaluateChangeTemporalNumericCollection(
        changeTemporalNumericCollection.changeMeasure,
        temporalNumericCollectionValues
    );
}

inline std::vector<double>
multiscale::verification::NumericMeasureCollectionVisitor::evaluateTemporalNumericMeasureCollection(
    const SpatialTemporalTrace &trace, unsigned long startTimepoint, unsigned long endTimepoint,
    const NumericMeasureType &numericMeasure
) const {
    std::vector<double> numericMeasureValues;

    SpatialTemporalTrace traceCopy(trace);

    // Compute the numeric measure values
    for (unsigned long i = startTimepoint; i <= endTimepoint; i = traceCopy.nextTimePointValue()) {
        traceCopy.setSubTrace(i);

        numericMeasureValues.push_back(
            boost::apply_visitor(NumericVisitor(traceCopy.getTimePoint(0)), numericMeasure)
        );
    }

    return numericMeasureValues;
}


#endif
