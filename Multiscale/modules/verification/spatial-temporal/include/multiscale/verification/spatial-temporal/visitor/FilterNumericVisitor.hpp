#ifndef FILTERNUMERICVISITOR_HPP
#define FILTERNUMERICVISITOR_HPP

#include "multiscale/verification/spatial-temporal/visitor/NumericEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/NumericVisitor.hpp"
#include "multiscale/verification/spatial-temporal/visitor/SpatialMeasureEvaluator.hpp"

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        //! Class for evaluating filter numeric measures
        class FilterNumericVisitor : public boost::static_visitor<double> {

            private:

                const TimePoint     &timePoint;     /*!< The considered timepoint */
                const SpatialEntity &spatialEntity; /*!< The considered spatial entity */

            public:

                FilterNumericVisitor(const TimePoint &timePoint, const SpatialEntity &spatialEntity)
                    : timePoint(timePoint), spatialEntity(spatialEntity) {}

                //! Overloading the "()" operator for the NumericMeasureAttribute alternative
                /*!
                 * \param numericMeasure  The numeric measure
                 */
                double operator()(const NumericMeasureAttribute &numericMeasure) const {
                    return evaluate(numericMeasure.numericMeasure);
                }

                //! Overloading the "()" operator for the SpatialMeasureAttribute alternative
                /*!
                 * \param spatialMeasure The spatial measure
                 */
                double operator()(const SpatialMeasureAttribute &spatialMeasure) const {
                    return SpatialMeasureEvaluator::evaluate(spatialEntity, spatialMeasure.spatialMeasureType);
                }

                //! Overloading the "()" operator for the UnaryNumericFilterAttribute alternative
                /*!
                 * \param unaryNumericFilter    The unary numeric filter
                 */
                double operator()(const UnaryNumericFilterAttribute &unaryNumericFilter) const {
                    double filterNumericMeasure = evaluate(unaryNumericFilter.filterNumericMeasure);

                    return NumericEvaluator::evaluate(unaryNumericFilter.unaryNumericMeasure.unaryNumericMeasureType,
                                                      filterNumericMeasure);
                }

                //! Overloading the "()" operator for the BinaryNumericFilterAttribute alternative
                /*!
                 * \param binaryNumericFilter   The binary numeric filter
                 */
                double operator()(const BinaryNumericFilterAttribute &binaryNumericFilter) const {
                    double firstFilterNumericMeasure    = evaluate(binaryNumericFilter.firstFilterNumericMeasure);
                    double secondFilterNumericMeasure   = evaluate(binaryNumericFilter.secondFilterNumericMeasure);

                    return NumericEvaluator::evaluate(binaryNumericFilter.binaryNumericMeasure.binaryNumericMeasureType,
                                                      firstFilterNumericMeasure, secondFilterNumericMeasure);
                }

                //! Overloading the "()" operator for the FilterNumericMeasureAttribute alternative
                /*!
                 * \param filterNumericMeasure   The filter numeric measure
                 */
                double operator()(const FilterNumericMeasureAttribute &filterNumericMeasure) const {
                    return evaluate(filterNumericMeasure.filterNumericMeasure);
                }

            private:

                //! Evaluate the given filter numeric measure considering the timePoint and spatialEntity fields
                /*!
                 * \param filterNumericMeasure  The given filter numeric measure
                 */
                double evaluate(const FilterNumericMeasureAttributeType &filterNumericMeasure) const {
                    return boost::apply_visitor(FilterNumericVisitor(timePoint, spatialEntity), filterNumericMeasure);
                }

                //! Evaluate the given numeric measure considering the timePoint field
                /*!
                 * \param numericMeasure The given numeric measure
                 */
                double evaluate(const NumericMeasureAttributeType &numericMeasure) const {
                    return boost::apply_visitor(NumericVisitor(timePoint), numericMeasure);
                }

        };

    };

};


#endif
