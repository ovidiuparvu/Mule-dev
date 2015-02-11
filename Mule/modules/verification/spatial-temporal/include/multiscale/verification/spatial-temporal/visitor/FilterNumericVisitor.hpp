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

                TimePoint                   &timePoint;             /*!< The considered timepoint */
                const SpatialEntity         &spatialEntity;         /*!< The considered spatial entity */
                const TypeSemanticsTable    &typeSemanticsTable;    /*!< The considered type semantics table */

            public:

                FilterNumericVisitor(TimePoint &timePoint, const SpatialEntity &spatialEntity,
                                     const TypeSemanticsTable &typeSemanticsTable)
                                     : timePoint(timePoint), spatialEntity(spatialEntity),
                                       typeSemanticsTable(typeSemanticsTable) {}

                //! Overloading the "()" operator for the FilterNumericMeasureAttribute alternative
                /*!
                 * \param filterNumericMeasure   The filter numeric measure
                 */
                double operator()(const FilterNumericMeasureAttribute &filterNumericMeasure) const {
                    return evaluate(filterNumericMeasure.filterNumericMeasure);
                }

                //! Overloading the "()" operator for the PrimaryNumericMeasureAttribute alternative
                /*!
                 * \param primaryNumericMeasure The primary numeric measure
                 */
                double operator()(const PrimaryNumericMeasureAttribute &primaryNumericMeasure) const {
                    return evaluate(primaryNumericMeasure.primaryNumericMeasure);
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

            private:

                //! Evaluate the given filter numeric measure considering the timePoint and spatialEntity fields
                /*!
                 * \param filterNumericMeasure  The given filter numeric measure
                 */
                double evaluate(const FilterNumericMeasureAttributeType &filterNumericMeasure) const {
                    return boost::apply_visitor(FilterNumericVisitor(timePoint, spatialEntity, typeSemanticsTable),
                                                filterNumericMeasure);
                }

                //! Evaluate the given primary numeric measure considering the timePoint field
                /*!
                 * \param primaryNumericMeasure The given primary numeric measure
                 */
                double evaluate(const PrimaryNumericMeasureAttributeType &primaryNumericMeasure) const {
                    return (
                        boost::apply_visitor(
                            NumericVisitor(timePoint, typeSemanticsTable),
                            primaryNumericMeasure
                        )
                    );
                }

        };

    };

};


#endif
