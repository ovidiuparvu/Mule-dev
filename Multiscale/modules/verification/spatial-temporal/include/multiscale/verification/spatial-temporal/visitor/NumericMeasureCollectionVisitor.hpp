#ifndef NUMERICMEASURECOLLECTIONVISITOR_HPP
#define NUMERICMEASURECOLLECTIONVISITOR_HPP

#include "multiscale/verification/spatial-temporal/visitor/NumericMeasureCollectionEvaluator.hpp"

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
                operator()(const TemporalNumericCollectionAttribute &temporalNumericCollection) const {
                    // TODO: Replace with the actual implementation + refactor evaluate method from
                    // NumericMeasureCollectionEvaluator class
                    return std::vector<double>();
                }

                //! Overloading the "()" operator for the SpatialMeasureCollectionAttribute alternative
                /*!
                 * \param spatialMeasureCollection  The spatial measure collection
                 */
                std::vector<double>
                operator()(const SpatialMeasureCollectionAttribute &spatialMeasureCollection) const {
                    return NumericMeasureCollectionEvaluator::evaluate(
                        trace.getTimePoint(0),
                        spatialMeasureCollection
                    );
                }

        };

    };

};


#endif
