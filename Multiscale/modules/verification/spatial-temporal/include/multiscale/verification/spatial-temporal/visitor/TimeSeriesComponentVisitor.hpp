#ifndef TIMESERIESCOMPONENTVISITOR_HPP
#define TIMESERIESCOMPONENTVISITOR_HPP

#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/verification/spatial-temporal/visitor/TimeSeriesComponentEvaluator.hpp"

#include <boost/variant.hpp>
#include <multiscale/verification/spatial-temporal/attribute/TimeSeriesComponentAttribute.hpp>
#include <functional>


namespace multiscale {

    namespace verification {

        //! Class for evaluating time series components
        /*!
         * The output values of the visitor is a collection of indices pointing to the
         * start and end positions of the time series components identified in the given collection of
         * values. In case of heterogeneous time series components the start position = end position,
         * while in the case of homogeneous time series components start position != end position.
         */
        class TimeSeriesComponentVisitor : public boost::static_visitor<std::vector<std::size_t>> {

            private:

                const std::vector<double> &values;   /*!< The collection of considered values */

            public:

                TimeSeriesComponentVisitor(const std::vector<double> &values) : values(values) {}

                //! Overloading the "()" operator for the HeterogeneousTimeSeriesComponentAttribute alternative
                /*!
                 * \param heterogeneousTimeSeriesComponent  The heterogeneous time series component
                 */
                std::vector<std::size_t>
                operator()(const HeterogeneousTimeSeriesComponentAttribute &heterogeneousTimeSeriesComponent) const {
                    switch (heterogeneousTimeSeriesComponent.heterogeneousTimeSeriesComponent) {
                        case HeterogeneousTimeSeriesComponentType::Peak:
                            return duplicateCollectionElements(
                                evaluateHeterogeneousComponentsIndices(values, std::less<double>())
                            );
                            break;

                        case HeterogeneousTimeSeriesComponentType::Valley:
                            return duplicateCollectionElements(
                                evaluateHeterogeneousComponentsIndices(values, std::greater<double>())
                            );
                            break;

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return std::vector<std::size_t>();
                }

                //! Overloading the "()" operator for the HomogeneousTimeSeriesComponentAttribute alternative
                /*!
                 * \param homogeneousTimeSeriesComponent  The homogeneous time series component
                 */
                std::vector<std::size_t>
                operator()(const HomogeneousTimeSeriesComponentAttribute &homogeneousTimeSeriesComponent) const {
                    return TimeSeriesComponentEvaluator::evaluate(
                        homogeneousTimeSeriesComponent,
                        values
                    );
                }

            private:

                //! Duplicate each element in the given indices collection
                std::vector<std::size_t>
                duplicateCollectionElements(const std::vector<std::size_t> &collection) const {
                    std::vector<std::size_t> duplicatedElementsCollection;

                    // Reserve the required amount of memory
                    duplicatedElementsCollection.reserve(collection.size() * 2);

                    // Add each element from old into new collection twice
                    for (auto element : collection) {
                        // Add element once
                        duplicatedElementsCollection.push_back(element);

                        // Add element twice
                        duplicatedElementsCollection.push_back(element);
                    }

                    return duplicatedElementsCollection;
                }

                //! Compute the set of indices pointing to the heterogeneous components in the given values collection
                /*! A value located at index i in the collection, 0 < i < (values.size() - 1), is a heterogeneous
                 *  component if and only if relation(values[i - 1], values[i]) and !relation(values[i], values[i + 1])
                 *  and !equal_to(values[i], values[i + 1])
                 *
                 * \param values            The collection of given values
                 * \param relation          The considered relation
                 */
                template <typename Relation>
                std::vector<std::size_t>
                evaluateHeterogeneousComponentsIndices(const std::vector<double> &values,
                                                       const Relation &relation) const {
                    std::vector<std::size_t> heterogeneousComponentsIndices;

                    // Stop at the last but one element index because both (index) and
                    // (index + 1) are considered below
                    std::size_t consideredValuesEndIndex = (values.size() > 0)
                                                               ? (values.size() - 1)
                                                               : 0;

                    // Compute the peak indices
                    for (std::size_t i = 1; i < consideredValuesEndIndex; i++) {
                        if ((relation(values[i - 1], values[i])) &&
                            (!relation(values[i], values[i + 1])) &&
                            (!std::equal_to<double>()(values[i], values[i + 1]))) {
                            heterogeneousComponentsIndices.push_back(i);
                        }
                    }

                    return heterogeneousComponentsIndices;
                }

        };

    };

};


#endif
