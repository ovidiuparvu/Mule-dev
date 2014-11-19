#ifndef NUMERICMEASURECOLLECTIONEVALUATOR_HPP
#define NUMERICMEASURECOLLECTIONEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"
#include "multiscale/verification/spatial-temporal/visitor/SubsetVisitor.hpp"
#include "multiscale/verification/spatial-temporal/visitor/TimePointEvaluator.hpp"


namespace multiscale {

    namespace verification {

        //! Class used to evaluate numeric measure collections
        class NumericMeasureCollectionEvaluator {

            public:

                //! Evaluate the given temporal numeric collection
                /*!
                 * \param trace                     The given spatial temporal trace
                 * \param typeSemanticsTable        The given type semantics table
                 * \param temporalNumericCollection The given temporal numeric collection
                 */
                static std::vector<double>
                evaluateTemporalNumericCollection(SpatialTemporalTrace &trace,
                                                  const TypeSemanticsTable &typeSemanticsTable,
                                                  const TemporalNumericCollectionAttribute
                                                  &temporalNumericCollection) {
                    return (
                        boost::apply_visitor(
                            NumericMeasureCollectionVisitor(trace, typeSemanticsTable),
                            temporalNumericCollection.temporalNumericCollection
                        )
                    );
                }

                //! Evaluate the spatial measure collection considering the given timepoint
                /*!
                 * \param timePoint                 The given timepoint
                 * \param typeSemanticsTable        The given type semantics table
                 * \param spatialMeasureCollection  The considered spatial measure collection
                 */
                static std::vector<double>
                evaluateSpatialMeasureCollection(TimePoint &timePoint,
                                                 const TypeSemanticsTable &typeSemanticsTable,
                                                 const SpatialMeasureCollectionAttribute
                                                 &spatialMeasureCollection) {
                    // Create the subset timepoint corresponding to the given timepoint
                    TimePoint subsetTimePoint(
                        boost::apply_visitor(
                            SubsetVisitor(timePoint, typeSemanticsTable),
                            spatialMeasureCollection.subset.subset
                        )
                    );

                    // Compute the spatial measure values corresponding to the above created
                    // subset timepoint
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
