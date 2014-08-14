#ifndef SPATIALMEASURECOLLECTIONEVALUATOR_HPP
#define SPATIALMEASURECOLLECTIONEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"
#include "multiscale/verification/spatial-temporal/visitor/SpatialMeasureEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/SubsetVisitor.hpp"


namespace multiscale {

    namespace verification {

        //! Class used to evaluate spatial measure collections
        class SpatialMeasureCollectionEvaluator {

            public:

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
