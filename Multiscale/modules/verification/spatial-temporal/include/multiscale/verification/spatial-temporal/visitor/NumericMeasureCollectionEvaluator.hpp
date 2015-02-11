#ifndef NUMERICMEASURECOLLECTIONEVALUATOR_HPP
#define NUMERICMEASURECOLLECTIONEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"


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
                                                 &spatialMeasureCollection);

        };

    };

};


// Includes added after class declaration to avoid include circular dependency errors

#include "multiscale/verification/spatial-temporal/visitor/SpatialMeasureCollectionVisitor.hpp"


// Methods which depend on the immediately above included classes

inline std::vector<double>
multiscale::verification::NumericMeasureCollectionEvaluator::evaluateSpatialMeasureCollection(
    TimePoint &timePoint, const TypeSemanticsTable &typeSemanticsTable,
    const SpatialMeasureCollectionAttribute &spatialMeasureCollection
) {
    return (
        boost::apply_visitor(
            SpatialMeasureCollectionVisitor(timePoint, typeSemanticsTable),
            spatialMeasureCollection.spatialMeasureCollection
        )
    );
}


#endif
