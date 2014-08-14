#ifndef NUMERICMEASURECOLLECTIONEVALUATOR_HPP
#define NUMERICMEASURECOLLECTIONEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"
#include "multiscale/verification/spatial-temporal/visitor/NumericVisitor.hpp"
#include "multiscale/verification/spatial-temporal/visitor/SpatialMeasureEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/SubsetVisitor.hpp"


namespace multiscale {

    namespace verification {

        //! Class used to evaluate numeric measure collections
        class NumericMeasureCollectionEvaluator {

            public:

                //! Evaluate the temporal numeric measure collection considering the given spatio-temporal trace
                /*!
                 * \param trace             The considered spatio-temporal trace
                 * \param startTimepoint    The considered start timepoint value
                 * \param endTimepoint      The considered end timepoint value
                 * \param numericMeasure    The numeric measure to be evaluated
                 */
                static std::vector<double>
                evaluate(const SpatialTemporalTrace &trace, unsigned long startTimepoint,
                         unsigned long endTimepoint, const NumericMeasureType &numericMeasure) {
                    std::vector<double> numericMeasureValues;

                    SpatialTemporalTrace traceCopy(trace);

                    for (unsigned long i = startTimepoint; i <= endTimepoint; i++) {
                        traceCopy.setSubTrace(i);

                        numericMeasureValues.push_back(
                            boost::apply_visitor(NumericVisitor(trace.getTimePoint(0)), numericMeasure)
                        );
                    }

                    return numericMeasureValues;
                }

                //! Evaluate the spatial measure collection considering the given timepoint
                /*!
                 * \param timePoint                 The given timepoint
                 * \param spatialMeasureCollection  The considered spatial measure collection
                 */
                static std::vector<double>
                evaluate(const TimePoint &timePoint,
                         const SpatialMeasureCollectionAttribute &spatialMeasureCollection) {
                    TimePoint subsetTimePoint(
                        boost::apply_visitor(
                            SubsetVisitor(timePoint),
                            spatialMeasureCollection.subset.subset
                        )
                    );

                    std::vector<double> spatialMeasureValues =
                        TimePointEvaluator::getSpatialMeasureValues(
                            subsetTimePoint,
                            spatialMeasureCollection.spatialMeasure.spatialMeasureType
                        );

                    return spatialMeasureValues;
                }

        };

    };

};


#endif
